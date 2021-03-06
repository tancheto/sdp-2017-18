#include "UnitTestFramework.h"

#include <algorithm>

#include "graph.cpp"

using TestGraph = Graph<int>;
using TestPath = Path<int>;
using TestPaths = Paths<int>;

TestGraph* createTestGraph() {
  TestGraph* g = new TestGraph;
  for(int i = 1; i <= 6; i++)
    g->addVertex(i);
  g->addEdge(1, 2);
  g->addEdge(1, 3);
  g->addEdge(2, 3);
  g->addEdge(2, 6);
  g->addEdge(3, 4);
  g->addEdge(3, 6);
  g->addEdge(4, 1);
  g->addEdge(4, 5);
  g->addEdge(5, 3);
  g->addEdge(6, 5);
  return g;
}

TEST_CASE("Graph", Graph_CreateEmptyVertices) {
  TestGraph g;
  Assert::IsTrue(g.vertices().empty());
}

TEST_CASE("Graph", Graph_VerticesList) {
  int i = 1;
  std::vector<int> vs = createTestGraph()->vertices();
  std::sort(vs.begin(), vs.end());
  for(int v : vs)
    Assert::AreEqual(i++, v);
  Assert::AreEqual(i, 7);
}

TEST_CASE("Graph", Graph_IsEdge) {
  TestGraph* g = createTestGraph();
  Assert::IsFalse(g->isEdge(1, 1));
  Assert::IsTrue (g->isEdge(1, 2));
  Assert::IsTrue (g->isEdge(1, 3));
  Assert::IsFalse(g->isEdge(2, 1));
  Assert::IsFalse(g->isEdge(2, 2));
  Assert::IsTrue (g->isEdge(2, 3));
  Assert::IsFalse(g->isEdge(3, 1));
  Assert::IsFalse(g->isEdge(3, 2));
  Assert::IsFalse(g->isEdge(3, 3));
}

TEST_CASE("Graph", Graph_AddEdge) {
  TestGraph* g = createTestGraph();
  Assert::IsFalse(g->isEdge(6, 4));
  Assert::IsTrue(g->addEdge(6, 4));
  Assert::IsTrue(g->isEdge(6, 4));
  Assert::IsFalse(g->addEdge(6, 4));
}

TEST_CASE("Graph", Graph_AddVertex) {
  TestGraph* g = createTestGraph();
  Assert::IsFalse(g->addVertex(6));
  Assert::IsTrue(g->addVertex(7));
  Assert::IsFalse(g->addVertex(7));
}

TEST_CASE("Graph", Graph_Successors) {
  TestGraph* g = createTestGraph();
  int i = 0;
  for(TestGraph::I it = g->successors(1); it; i += *it++)
    Assert::IsTrue(*it == 2 || *it == 3);
  Assert::AreEqual(i, 5);
  i = 0;
  for(TestGraph::I it = g->successors(2); it; i += *it++)
    Assert::IsTrue(*it == 3 || *it == 6);
  Assert::AreEqual(i, 9);
  i = 0;
  for(TestGraph::I it = g->successors(3); it; i += *it++)
    Assert::IsTrue(*it == 4 || *it == 6);
  Assert::AreEqual(i, 10);
}

TEST_CASE("Graph", Graph_NoSuccessorsEmpty) {
  Assert::IsTrue(noSuccessors(*createTestGraph()).empty());
}

TEST_CASE("Graph", Graph_NoSuccessorsTest) {
  TestGraph g;
  g.addVertex(1);
  g.addVertex(2);
  g.addEdge(1, 2);
  std::vector<int> ns = noSuccessors(g);
  Assert::AreEqual(ns.size(), 1);
  Assert::AreEqual(ns[0], 2);
}

TEST_CASE("Graph", Graph_PredecessorsTest) {
  std::vector<int> pred = predecessors(*createTestGraph(), 2);
  Assert::AreEqual(pred.size(), 1);
  Assert::AreEqual(pred[0], 1);
}

TEST_CASE("Graph", Graph_IsNotSymmetric) {
  Assert::IsFalse(isSymmetric(*createTestGraph()));
}

TEST_CASE("Graph", Graph_IsSymmetric) {
  TestGraph g;
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(3);
  g.addEdge(1, 2);
  g.addEdge(2, 1);
  Assert::IsTrue(isSymmetric(g));
}

TEST_CASE("Graph", Graph_hasPathDFS) {
  TestGraph* g = createTestGraph();
  for(int i = 1; i <= 6; i++)
    for(int j = i + 1; j <= 6; j++) {
      Assert::IsTrue(hasPathDFS(*g, i, j));
      Assert::IsTrue(hasPathDFS(*g, j, i));
    }
}

TEST_CASE("Graph", Graph_hasPathBFS) {
  TestGraph* g = createTestGraph();
  for(int i = 1; i <= 6; i++)
    for(int j = i + 1; j <= 6; j++) {
      Assert::IsTrue(hasPathBFS(*g, i, j));
      Assert::IsTrue(hasPathBFS(*g, j, i));
    }
}

TEST_CASE("Graph", Graph_findPathDFS) {
  TestGraph* g = createTestGraph();
  TestPath path = findPathDFS(*g, 1, 6);
  Assert::IsFalse(path.empty());
  // printPath(path);
  Assert::AreEqual(path.peek(), 6);
  Assert::IsTrue(isPath(*g, path));
}

TEST_CASE("Graph", Graph_findPathBFS) {
  TestGraph* g = createTestGraph();
  TestPath path = findPathBFS(*g, 1, 6);
  Assert::IsFalse(path.empty());
  // printPath(path);
  Assert::AreEqual(path.peek(), 6);
  Assert::IsTrue(isPath(*g, path));
}

TEST_CASE("Graph", Graph_allPathsDFS) {
  TestGraph* g = createTestGraph();
  TestPaths paths = allPathsDFS(*g, 1, 6);
  for(TestPaths::I it = paths.begin(); it; ++it) {
    Assert::IsFalse((*it).empty());
    // printPath(*it);
    Assert::AreEqual((*it).peek(), 6);
    Assert::IsTrue(isPath(*g, *it));
  }
}

TEST_CASE("Graph", Graph_allPathsBFS) {
  TestGraph* g = createTestGraph();
  TestPaths paths = allPathsBFS(*g, 1, 6);
  for(TestPaths::I it = paths.begin(); it; ++it) {
    Assert::IsFalse((*it).empty());
    // printPath(*it);
    Assert::AreEqual((*it).peek(), 6);
    Assert::IsTrue(isPath(*g, *it));
  }
}
