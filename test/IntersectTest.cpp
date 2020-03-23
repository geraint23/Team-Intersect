#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/Circle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntersectTest
{
	TEST_CLASS(IntersectTest)
	{
	public:

		TEST_METHOD(TestMethod1)	// 直线与直线
		{
			Line l1 = Line(0, 1, 1, 0);	// 相交
			Line l2 = Line(0, 0, 1, 1);
			l1.intersect_L(l2);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			l1 = Line(1, 2, 3, 4);	// 平行
			l2 = Line(5, 7, 7, 9);
			l1.intersect_L(l2);
			Assert::AreEqual(0, (int)nodes.size());
		}

		TEST_METHOD(TestMethod2)	// 直线与射线
		{
			nodes.clear();
			Line l1 = Line(0, 1, 1, 0);	// 相交
			Ray r1 = Ray(0, 0, 1, 1);
			r1.intersect_L(l1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			l1 = Line(0, 1, 1, 0);	// 在同一直线但无交点
			r1 = Ray(0, 0, -1, -1);
			r1.intersect_L(l1);
			Assert::AreEqual(0, (int)nodes.size());
		}

		TEST_METHOD(TestMethod3)	// 直线与圆
		{
			nodes.clear();
			Line l1 = Line(0, 1, 1, 0);	// 相交，两个交点
			Circle c1 = Circle(0, 0, 1);
			c1.intersect_L(l1);
			Assert::AreEqual(2, (int)nodes.size());

			nodes.clear();
			l1 = Line(1, 0, 1, 1);	// 相切
			c1 = Circle(0, 0, 1);
			c1.intersect_L(l1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			l1 = Line(2, 0, 2, 1);	// 相离
			c1 = Circle(0, 0, 1);
			c1.intersect_L(l1);
			Assert::AreEqual(0, (int)nodes.size());
		}

		TEST_METHOD(TestMethod4)	// 直线与线段
		{
			nodes.clear();
			Line l1 = Line(0, 1, 1, 0);	// 相交
			Segment s1 = Segment(0, 0, 1, 1);
			s1.intersect_L(l1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			l1 = Line(1, 0, 1, 1);	// 线段所在直线与直线相交，但线段不交
			s1 = Segment(0, 0, -1, -1);
			s1.intersect_L(l1);
			Assert::AreEqual(0, (int)nodes.size());

		}

		TEST_METHOD(TestMethod5) // 圆和射线
		{
			nodes.clear();
			Circle c1 = Circle(0, 0, 1);	// 一个交点，不切，起点不在圆上
			Ray r1 = Ray(0, 0, 1, 1);
			c1.intersect_R(r1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 一个交点，相切
			r1 = Ray(-3, 1, -2, 1);
			c1.intersect_R(r1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 一个交点，起点在圆上
			r1 = Ray(0, 1, 0, 2);
			c1.intersect_R(r1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 两个交点，起点在圆上
			r1 = Ray(0, 1, 0, -1);
			c1.intersect_R(r1);
			Assert::AreEqual(2, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 两个交点，正常情况
			r1 = Ray(-1, -2, 0, 0);
			c1.intersect_R(r1);
			Assert::AreEqual(2, (int)nodes.size());
		}

		TEST_METHOD(TestMethod6) // 圆和线段
		{
			nodes.clear();
			Circle c1 = Circle(0, 0, 2);	// 线段在圆内，无交点
			Segment s1 = Segment(-1, 0, 1, 0);
			c1.intersect_S(s1);
			Assert::AreEqual(0, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 两个交点，两端点在圆上
			s1 = Segment(1, 0, -1, 0);
			c1.intersect_S(s1);
			Assert::AreEqual(2, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 一个交点
			s1 = Segment(0, 2, 0, 0);
			c1.intersect_S(s1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 在圆外，无交点
			s1 = Segment(12, 13, 13, 14);
			c1.intersect_S(s1);
			Assert::AreEqual(0, (int)nodes.size());
		}

		TEST_METHOD(TestMethod7) // 圆和圆
		{
			nodes.clear();
			Circle c1 = Circle(0, 0, 1);	// 内含
			Circle c2 = Circle(0, 0, 2);
			c1.intersect_C(c2);
			Assert::AreEqual(0, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 外离
			c2 = Circle(5, 0, 1);
			c1.intersect_C(c2);
			Assert::AreEqual(0, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 2);	// 内切
			c2 = Circle(1, 0, 1);
			c1.intersect_C(c2);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 外切
			c2 = Circle(2, 0, 1);
			c1.intersect_C(c2);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			c1 = Circle(0, 0, 1);	// 相交
			c2 = Circle(1, 0, 1);
			c1.intersect_C(c2);
			Assert::AreEqual(2, (int)nodes.size());
		}

		TEST_METHOD(TestMethod8) // 射线和射线
		{
			nodes.clear();
			Ray r1 = Ray(0, 0, 1, 0);	// 起点重合，一个交点
			Ray r2 = Ray(0, 0, -2, 0);
			r1.intersect_R(r2);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			r1 = Ray(0, 0, 1, 0);	// 一个起点在另一个射线上，一个交点
			r2 = Ray(2, 0, 0, 1);
			r1.intersect_R(r2);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			r1 = Ray(0, 0, 1, 0);	// 正常情况一个交点
			r2 = Ray(2, -1, 3, 5);
			r1.intersect_R(r2);
			Assert::AreEqual(1, (int)nodes.size());
		}

		TEST_METHOD(TestMethod9) // 射线和线段
		{
			nodes.clear();
			Ray r1 = Ray(0, 0, 1, 0);	// 起点重合，一个交点
			Segment s1 = Segment(0, 0, -2, 0);
			s1.intersect_R(r1);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			r1 = Ray(0, 0, 1, 1);	// 在同一条直线上，无交点
			s1 = Segment(-2, -2, -2, -1);
			s1.intersect_R(r1);
			Assert::AreEqual(0, (int)nodes.size());

			nodes.clear();
			r1 = Ray(0, 0, 1, 1);	// 不在同一条直线上，不平行，无交点
			s1 = Segment(1, 0, 2, -2);
			s1.intersect_R(r1);
			Assert::AreEqual(0, (int)nodes.size());
		}

		TEST_METHOD(TestMethod10) // 线段和线段
		{
			nodes.clear();
			Segment s1 = Segment(0, 0, 1, 0);	// 起点重合，一个交点
			Segment s2 = Segment(0, 0, -2, 0);
			s1.intersect_S(s2);
			Assert::AreEqual(1, (int)nodes.size());

			nodes.clear();
			s1 = Segment(0, 0, 1, 1);	// 在同一条直线上，无交点
			s2 = Segment(-2, -2, -2, -1);
			s1.intersect_S(s2);
			Assert::AreEqual(0, (int)nodes.size());

			nodes.clear();
			s1 = Segment(0, 0, 1, 1);	// 不在同一条直线上，不平行，无交点
			s2 = Segment(1, 0, 2, -2);
			s1.intersect_S(s2);
			Assert::AreEqual(0, (int)nodes.size());
		}

		TEST_METHOD(TestMethod11)	//	四种对象混合
		{
			Line l = Line(0, 5, 4, 8);
			Circle c = Circle(0, 0, 3);
			Ray r = Ray(1, 0, 4, 3);
			Segment s = Segment(-2, 1, 5, 6);
			c.intersect_L(l);
			c.intersect_R(r);
			c.intersect_S(s);
			r.intersect_L(l);
			s.intersect_L(l);
			s.intersect_R(r);
			Assert::AreEqual(3, (int)nodes.size());
		}
	};
}
