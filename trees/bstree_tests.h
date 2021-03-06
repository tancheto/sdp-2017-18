#include "UnitTestFramework.h"
#include "bstree.cpp"

using TestBSTree = BSTree<int>;

TEST_CASE("BSTree", BSTree_CreateEmpty) {
  TestBSTree t;
  Assert::IsTrue(t.empty());
}

TEST_CASE("BSTree", BSTree_CreateSingle) {
  TestBSTree t;
  Assert::IsTrue(t.insert(5));
  // t.printDOT(std::clog);
  Assert::IsFalse(t.empty());
  Assert::IsTrue(t.search(5));
  Assert::IsFalse(t.search(7));
}

TEST_CASE("BSTree", BSTree_InsertTwice) {
  TestBSTree t;
  Assert::IsTrue(t.insert(5));
  Assert::IsFalse(t.insert(5));
}

TestBSTree* createTestBSTree() {
  TestBSTree* t = new TestBSTree;
  t->insert(5);
  t->insert(3);
  t->insert(7);
  t->insert(4);
  t->insert(6);
  t->insert(2);
  t->insert(1);
  return t;
}

TEST_CASE("BSTree", BSTree_SearchAll) {
  TestBSTree* t = createTestBSTree();
  //  t.printDOT(std::clog);
  for(int i = 1; i <= 7; i++)
    Assert::IsTrue(t->search(i));
}

TEST_CASE("BSTree", BSTree_CollectSorted) {
  TestBSTree* t = createTestBSTree();
  //  t.printDOT(std::clog);
  LinkedList<int> l;
  t->collect(l);
  int i = 1;
  for(LinkedListIterator<int> it = l.begin(); it; ++it, ++i)
    Assert::AreEqual(*it, i);
  Assert::AreEqual(i, 8);
}

TEST_CASE("BSTree", BSTree_RemoveAll) {
  TestBSTree* t = createTestBSTree();
  int toRemove[] = { 4, 2, 7, 1, 5, 3, 6 };
  for(int i = 0; i < 7; i++) {
    int x = toRemove[i];
    Assert::IsTrue(t->search(x));
    Assert::IsTrue(t->remove(x));
    Assert::IsFalse(t->search(x));
    Assert::IsFalse(t->remove(x));
  }
  Assert::IsTrue(t->empty());
}
