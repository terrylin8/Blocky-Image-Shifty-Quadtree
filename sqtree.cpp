#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int, int> ul, int w, int h, RGBAPixel a, double v)
    : upLeft(ul), width(w), height(h), avg(a), var(v), NW(NULL), NE(NULL),
      SE(NULL), SW(NULL) {}

// Second Node constructor, given
SQtree::Node::Node(stats &s, pair<int, int> ul, int w, int h)
    : upLeft(ul), width(w), height(h), NW(NULL), NE(NULL), SE(NULL), SW(NULL)
{
  avg = s.getAvg(ul, w, h);
  var = s.getVar(ul, w, h);
}

// SQtree destructor, given.
SQtree::~SQtree() { clear(); }

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree &other) { copy(other); }

// SQtree assignment operator, given.
SQtree &SQtree::operator=(const SQtree &rhs)
{
  if (this != &rhs)
  {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG &imIn, double tol)
{
  stats s(imIn);
  pair<int, int> ul = make_pair(0, 0);
  root = buildTree(s, ul, imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node *SQtree::buildTree(stats &s, pair<int, int> &ul, int w, int h,
                                double tol)
{
  if (h * w == 0)
  {
    return NULL;
  }

  Node *curr = new Node(s, ul, w, h);

  if ((w == 1 && h == 1) || (s.getVar(ul, w, h) <= tol))
  {
    return curr;
  }

  double minvariance = s.getVar(ul, w, h);
  int bestx = 0;
  int besty = 0;

for (int x = 0; x < w; x++) {
    for (int y = 0; y < h; y++) {
      if (!(x == 0 && y == 0)) {

        double maxvariance = -1;

        if (x > 0 && y > 0) {
          double d0 = s.getVar(ul, x, y);
          maxvariance = max(maxvariance, d0);
        }
        if (y > 0) {
          pair<int, int> ul1 = make_pair(x + ul.first, ul.second);
          double d1 = s.getVar(ul1, w - x, y);
          maxvariance = max(maxvariance, d1);
        }
        if (x > 0) {
          pair<int, int> ul2 = make_pair(ul.first, ul.second + y);
          double d2 = s.getVar(ul2, x, h - y);
          maxvariance = max(maxvariance, d2);
        }

        pair<int, int> ul3 = make_pair(ul.first + x, ul.second + y);
        double d3 = s.getVar(ul3, w - x, h - y);
        maxvariance = max(maxvariance, d3);

        if (maxvariance < minvariance) {
          minvariance = maxvariance;
          bestx = x;
          besty = y;
        }
      }
    }
  }
  if (bestx > 0 && besty > 0) {
    curr->NW = buildTree(s, ul, bestx, besty, tol);
  }
  if (besty > 0) {
    pair<int, int> ul1 = make_pair(bestx + ul.first, ul.second);
    curr->NE = buildTree(s, ul1, w - bestx, besty, tol);
  }
  if (bestx > 0) {
    pair<int, int> ul2 = make_pair(ul.first, ul.second + besty);
    curr->SW = buildTree(s, ul2, bestx, h - besty, tol);
  }

  pair<int, int> ul3 = make_pair(ul.first + bestx, ul.second + besty);
  curr->SE = buildTree(s, ul3, w - bestx, h - besty, tol);
  return curr;
}

/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render()
{
  PNG im(root->width, root->height);
  render(im, root);
  return im;
}

void SQtree::render(PNG &im, Node *curr)
{
  if (!curr)
  {
    return;
  }
  //check if node is a leaf
  if (!(curr->NW || curr->NE || curr->SE || curr->SW))
  {
    for (int x = curr->upLeft.first; x < curr->upLeft.first + curr->width;
         x++)
    {
      for (int y = curr->upLeft.second; y < curr->upLeft.second + curr->height;
           y++)
      {
        RGBAPixel *pix = im.getPixel(x, y);
        *pix = curr->avg;
      }
    }
  }
  else
  {
    render(im, curr->NW);
    render(im, curr->NE);
    render(im, curr->SE);
    render(im, curr->SW);
  }
}

/**
 * Delete allocated memory.
 */
void SQtree::clear() { clear(root); }

void SQtree::clear(Node *&n)
{
  if (n != NULL)
  {
    clear(n->NW);
    clear(n->NE);
    clear(n->SE);
    clear(n->SW);
    delete n;
    n = NULL;
  }
}

void SQtree::copy(const SQtree &other)
{
  Node *otheroot = other.root;
  root = copy(otheroot);
}

SQtree::Node *SQtree::copy(const Node *n)
{
  if (n)
  {
    Node *temp = new Node(n->upLeft, n->width, n->height, n->avg, n->var);
    temp->NE = copy(n->NE);
    temp->NW = copy(n->NW);
    temp->SE = copy(n->SE);
    temp->SW = copy(n->SW);
    return temp;
  }
  else
  {
    return NULL;
  }
}

int SQtree::size() { return size(root); }

int SQtree::size(const Node *n)
{
  if (n != NULL)
  {
    return 1 + size(n->NW) + size(n->NE) + size(n->SE) + size(n->SW);
  }
  return 0;
}
