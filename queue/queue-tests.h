#include "UnitTestFramework.h"

// ще смятаме, че шаблонът, който тестваме е TestQueue

TEST_CASE("Queue", Queue_CreateEmptyQueue) {
  const TestQueue<int> q;
  Assert::IsTrue(q.empty());
}

TEST_CASE("Queue", Queue_EnqueueNotEmpty) {
  TestQueue<int> q;
  q.enqueue(5);
  Assert::IsTrue(!q.empty());
}

TEST_CASE("Queue", Queue_EnqueueHead) {
  TestQueue<int> q;
  for(int i = 1; i <= 100; i++)
    q.enqueue(i);
  Assert::AreEqual(q.head(), 1);
}

TEST_CASE("Queue", Queue_EnqueueDequeue) {
  TestQueue<int> q;
  for(int i = 1; i <= 100; i++)
    q.enqueue(i);
  for(int i = 1; i <= 100; i++)
    Assert::AreEqual(q.dequeue(), i);
  Assert::IsTrue(q.empty());
}
  
TEST_CASE("Queue", Queue_DequeueAfterEnqueue) {
  TestQueue<int> q;
  for(int i = 1; i <= 1000; i++) {
    q.enqueue(i);
    Assert::AreEqual(q.dequeue(), i);
  }
  Assert::IsTrue(q.empty());
}
    
