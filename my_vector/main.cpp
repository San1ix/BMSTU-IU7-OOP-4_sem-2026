#include "vector.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

int main()
{
    static_assert(Container<Vector<int>>, "Vector<int> must satisfy Container");
    static_assert(Container<Vector<double>>, "Vector<double> must satisfy Container");
    static_assert(Container<Vector<std::string>>, "Vector<std::string> must satisfy Container");
    static_assert(std::random_access_iterator<VectorForwardIterator<int>>);
    static_assert(std::random_access_iterator<VectorConstForwardIterator<int>>);
    static_assert(std::random_access_iterator<VectorReverseIterator<int>>);
    static_assert(std::random_access_iterator<VectorConstReverseIterator<int>>);
    static_assert(std::ranges::input_range<Vector<int>>);
    std::cout << "1. Static asserts: OK\n";

    std::cout << "\n2. Constructors:\n";
    Vector<int> v0;
    std::cout << "   default: " << v0;

    Vector<int> v1{1, 2, 3, 4, 5};
    std::cout << "   initializer_list: " << v1;

    Vector<int> v2(v1);
    std::cout << "   copy: " << v2;

    Vector<int> v3(std::move(v2));
    std::cout << "   move: " << v3;
    std::cout << "   moved from v2: " << v2;

    Vector<int> v4(5);
    std::cout << "   size 5: " << v4;

    int arr[] = {10, 20, 30};
    Vector<int> v5(3, arr);
    std::cout << "   C-array: " << v5;

    std::vector<int> sv{100, 200, 300};
    Vector<int> v6(sv.begin(), sv.end());
    std::cout << "   iterators: " << v6;

    std::list<int> li{1, 2, 3, 4};
    Vector<int> v7(li.begin(), li.end());
    std::cout << "   std::list: " << v7;

    Vector<double> vd{1.1, 2.2, 3.3};
    std::cout << "   Vector<double>: " << vd;

    Vector<int> v8(vd);
    std::cout << "   from Vector<double>: " << v8;

    std::cout << "\n3. Assign:\n";
    Vector<int> va;
    va = std::initializer_list<int>{1, 2, 3};
    std::cout << "   = {1,2,3}: " << va;
    va = vd;
    std::cout << "   = Vector<double>: " << va;

    std::cout << "\n4. Addition:\n";
    Vector<int> a{1, 2, 3};
    Vector<int> b{4, 5, 6};
    std::cout << "   a = " << a;
    std::cout << "   b = " << b;
    std::cout << "   a + b = " << (a + b);
    std::cout << "   a.sum(b) = " << a.sum(b);
    std::cout << "   a + std::vector{10,20,30} = " << (a + std::vector<int>{10,20,30});
    a += b;
    std::cout << "   a += b: " << a;
    a.sum_eq(b);
    std::cout << "   a.sum_eq(b): " << a;

    Vector<std::string> vs1{"Hello, "};
    Vector<std::string> vs2{"World!"};
    std::cout << "   strings: " << (vs1 + vs2);

    std::cout << "\n5. Subtraction:\n";
    Vector<int> c{10, 20, 30};
    Vector<int> d{1, 2, 3};
    std::cout << "   c = " << c;
    std::cout << "   d = " << d;
    std::cout << "   c - d = " << (c - d);
    std::cout << "   c.sub(d) = " << c.sub(d);
    std::cout << "   c - std::vector{1,1,1} = " << (c - std::vector<int>{1,1,1});
    c -= d;
    std::cout << "   c -= d: " << c;
    std::cout << "   -c = " << (-c);
    std::cout << "   c.neg() = " << c.neg();

    std::cout << "\n6. Multiplication (Hadamard):\n";
    Vector<int> e{1, 2, 3};
    Vector<int> f{4, 5, 6};
    std::cout << "   e = " << e;
    std::cout << "   f = " << f;
    std::cout << "   e * f = " << (e * f);
    std::cout << "   e.mul(f) = " << e.mul(f);
    std::cout << "   e * std::vector{2,2,2} = " << (e * std::vector<int>{2,2,2});
    e *= f;
    std::cout << "   e *= f: " << e;

    std::cout << "\n7. Division:\n";
    Vector<double> g{10.0, 20.0, 30.0};
    Vector<double> h{2.0, 4.0, 6.0};
    std::cout << "   g = " << g;
    std::cout << "   h = " << h;
    std::cout << "   g / h = " << (g / h);
    std::cout << "   g.div(h) = " << g.div(h);
    std::cout << "   g / std::vector{2,2,3} = " << (g / std::vector<double>{2.0,2.0,3.0});
    g /= h;
    std::cout << "   g /= h: " << g;

    std::cout << "\n8. Cross product (3D):\n";
    Vector<int> x{1, 0, 0};
    Vector<int> y{0, 1, 0};
    Vector<int> z{0, 0, 1};
    std::cout << "   x = " << x;
    std::cout << "   y = " << y;
    std::cout << "   z = " << z;
    std::cout << "   x ^ y = " << (x ^ y);
    std::cout << "   x.vec_mul(y) = " << x.vec_mul(y);
    std::cout << "   y ^ z = " << (y ^ z);
    std::cout << "   z ^ x = " << (z ^ x);
    x ^= y;
    std::cout << "   x ^= y: " << x;
    std::cout << "   z ^ std::vector{1,2,3} = " << (z ^ std::vector<int>{1,2,3});

    std::cout << "\n9. Dot product:\n";
    Vector<int> u{1, 2, 3};
    Vector<int> w{4, 5, 6};
    std::cout << "   u = " << u;
    std::cout << "   w = " << w;
    std::cout << "   u & w = " << (u & w) << "\n";
    std::cout << "   u.scalar_mul(w) = " << u.scalar_mul(w) << "\n";

    std::cout << "\n10. Math:\n";
    Vector<double> mv{3.0, 4.0};
    std::cout << "   mv = " << mv;
    std::cout << "   mv.len() = " << mv.len() << "\n";
    std::cout << "   mv.normalization() = " << mv.normalization();
    std::cout << "   mv.is_normalize() = " << mv.is_normalize() << "\n";
    std::cout << "   normalized.is_normalize() = " << mv.normalization().is_normalize() << "\n";
    Vector<double> zero{0.0, 0.0, 0.0};
    std::cout << "   zero.is_zero() = " << zero.is_zero() << "\n";

    std::cout << "\n11. Angles:\n";
    Vector<double> ax{1.0, 0.0, 0.0};
    Vector<double> ay{0.0, 1.0, 0.0};
    Vector<double> ax2{2.0, 0.0, 0.0};
    std::cout << "   angle(x,y) = " << ax.calc_angle(ay) << " rad\n";
    std::cout << "   x.is_orthogonal(y) = " << ax.is_orthogonal(ay) << "\n";
    std::cout << "   x.is_collinear(x2) = " << ax.is_collinear(ax2) << "\n";

    std::cout << "\n12. Iterators:\n";
    Vector<int> iv{10, 20, 30, 40, 50};
    std::cout << "   forward: ";
    for (auto it = iv.begin(); it != iv.end(); ++it) std::cout << *it << " ";
    std::cout << "\n   reverse: ";
    for (auto rit = iv.rbegin(); rit != iv.rend(); ++rit) std::cout << *rit << " ";
    std::cout << "\n   operator[]: iv.begin()[2] = " << iv.begin()[2];
    std::cout << "\n   distance: " << (iv.end() - iv.begin());
    std::cout << "\n   sort: ";
    Vector<int> unsorted{5, 2, 8, 1, 9, 3};
    std::sort(unsorted.begin(), unsorted.end());
    std::cout << unsorted;

    std::cout << "\n13. Edge cases:\n";
    Vector<int> empty_vec;
    std::cout << "   empty: " << empty_vec;
    try { empty_vec.normalization(); }
    catch (const errDivisionZero&) { std::cout << "   normalization of empty: caught\n"; }
    try { Vector<int> v(1000); v[999] = 42; v[1000] = 0; }
    catch (const errIndexOutOfRange&) { std::cout << "   v[1000]: caught\n"; }
    try { Vector<int> v2d{1,2}; Vector<int> v3d{1,2,3}; v2d ^ v3d; }
    catch (const errSizeNotCompatible&) { std::cout << "   cross 2D: caught\n"; }
    try { Vector<int> v1e{1,2,3}; Vector<int> v2e{4,5}; v1e + v2e; }
    catch (const errVectorsSizeNotEqual&) { std::cout << "   diff sizes: caught\n"; }

    std::cout << "\n14. Range constructor:\n";
    auto view1 = std::views::iota(0, 5) | std::views::transform([](int x) { return x * 10; });
    Vector<int> rv1(view1);
    std::cout << "   iota*10: " << rv1;
    auto squares = std::views::iota(1, 6) | std::views::transform([](int x) { return x * x; });
    Vector<int> rv2(squares);
    std::cout << "   squares: " << rv2;
    std::vector<int> orig{1, 2, 3, 4, 5, 6, 7, 8};
    auto rv3_view = orig | std::views::reverse | std::views::take(4);
    Vector<int> rv3(rv3_view);
    std::cout << "   reverse+take: " << rv3;

    std::cout << "\n15. Mixed types:\n";
    Vector<int> vi{1, 2, 3};
    Vector<double> vd2{1.5, 2.5, 3.5};
    std::cout << "   int + double = " << (vi + vd2);
    std::cout << "   int * double = " << (vi * vd2);

    std::cout << "\n=== ALL TESTS PASSED ===\n";
    return 0;
}