#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>
#include <cmath>
#include "Vector2.hpp"
#include "Matrix4.hpp"

void test_identity_and_zero() {
  Matrix4x4 identity = Matrix4x4::identity();
  Matrix4x4 zero = Matrix4x4::zero();

  // Identity diagonal = 1
  for (int i = 0; i < 4; ++i)
    assert(identity.m[i][i] == 1.0f);

  // Zero matrix = all 0
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      assert(zero.m[i][j] == 0.0f);
}

void test_translation() {
  Matrix4x4 trans = Matrix4x4::translate(3.0f, 4.0f);
  vec2f v(1.0f, 2.0f);
  vec2f result = trans * v;

  assert(result == vec2f(4.0f, 6.0f));
}

void test_scaling() {
  Matrix4x4 scale = Matrix4x4::scale(2.0f, 3.0f);
  vec2f v(1.0f, 1.0f);
  vec2f result = scale * v;

  assert(result == vec2f(2.0f, 3.0f));
}

void test_rotation_z() {
  Matrix4x4 rot = Matrix4x4::rotateZ(M_PI_2); // 90 degrees
  vec2f v(1.0f, 0.0f);
  vec2f result = rot * v;

  // Should be ~ (0,1)
  assert(std::abs(result.x) < 1e-5);
  assert(std::abs(result.y - 1.0f) < 1e-5);
}

void test_matrix_multiplication() {
  Matrix4x4 t = Matrix4x4::translate(1.0f, 2.0f);
  Matrix4x4 s = Matrix4x4::scale(2.0f, 2.0f);
  Matrix4x4 combo = t * s;

  vec2f v(1.0f, 1.0f);
  vec2f result = combo * v;

  // scale (2,2) → (2,2), translate (1,2) → (3,4)
  assert(result == vec2f(3.0f, 4.0f));
}

void test_transpose() {
  Matrix4x4 m = Matrix4x4::identity();
  m.m[0][1] = 5.0f;
  Matrix4x4 mt = m.transpose();

  assert(mt.m[1][0] == 5.0f);
  assert(mt.m[0][1] == 0.0f);
}

void test_ortho_projection() {
  Matrix4x4 ortho = Matrix4x4::ortho(-1, 1, -1, 1, -1, 1);
  vec2f v(1.0f, 1.0f);
  vec2f projected = ortho * v;

  assert(std::abs(projected.x - 1.0f) < 1e-5);
  assert(std::abs(projected.y - 1.0f) < 1e-5);
}

void test_perspective_projection() {
  Matrix4x4 persp = Matrix4x4::perspective(M_PI / 2.0f, 1.0f, 0.1f, 100.0f);
  std::cout << "Perspective matrix:\n" << persp << std::endl;
}

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif

void v1_must_equal_to_v2() {
  vec2f v1(10, 10);
  vec2f v2;
  v2 = v1;
  assert(v1 == v2);
}

void t_copy_constructor() {
  vec2f v1(10, 10);
  vec2f v2(v1);
  assert(v1 == v2);
}

void t_v1_plus_v2() {
  vec2f v1(10, 15);
  vec2f v2(20, 25);
  vec2f v3 = v1 + v2;
  assert(v3 == vec2f(30, 40));
}

void t_v1_plus_equal_v2() {
  vec2f v1(10, 15);
  vec2f v2(20, 25);
  v1 += v2;
  assert(v1 == vec2f(30, 40));
}

void t_scalar_multiplication() {
  vec2f v(3, 4);
  vec2f result = v * 2.0f;
  assert(result == vec2f(6, 8));
}

void t_scalar_division() {
  vec2f v(6, 8);
  vec2f result = v / 2.0f;
  assert(result == vec2f(3, 4));
}

void t_dot_product() {
  vec2f a(1, 2), b(3, 4);
  float dot = a.dot(b);  // 1*3 + 2*4 = 11
  assert(dot == 11.0f);
}

void t_cross_product() {
  vec2f a(1, 2), b(3, 4);
  float cross = a.cross(b);  // 1*4 - 2*3 = -2
  assert(cross == -2.0f);
}

void t_magnitude() {
  vec2f v(3, 4);
  assert(std::abs(v.magnitude() - 5.0f) < 1e-6);
}

void t_normalization() {
  vec2f v(3, 4);
  vec2f n = v.normalized();
  assert(std::abs(n.magnitude() - 1.0f) < 1e-6);
}

void t_angle_between() {
  vec2f a(1, 0), b(0, 1);
  float angle = a.angleBetween(b); // Should be around pi/2
  assert(std::abs(angle - M_PI_2) < 1e-5);
}

void t_comparisons() {
  vec2f a(5, 5), b(5, 5), c(4, 5);
  assert(a == b);
  assert(a != c);
}

void t_static_vectors() {
  vec2f one = vec2f::ones();
  vec2f zero = vec2f::zeros();
  vec2f up = vec2f::up();
  assert(one == vec2f(1, 1));
  assert(zero == vec2f(0, 0));
  assert(up == vec2f(0, 1));
}

int main(void)
{
   v1_must_equal_to_v2();
  t_copy_constructor();
  t_v1_plus_v2();
  t_v1_plus_equal_v2();
  t_scalar_multiplication();
  t_scalar_division();
  t_dot_product();
  t_cross_product();
  t_magnitude();
  t_normalization();
  t_angle_between();
  t_comparisons();
  t_static_vectors();

  std::cout << "✅ All Vector2 tests passed successfully!\n";
  
  test_identity_and_zero();
  test_translation();
  test_scaling();
  test_rotation_z();
  test_matrix_multiplication();
  test_transpose();
  test_ortho_projection();
  test_perspective_projection();

  std::cout << "✅ All Matrix4x4 tests passed successfully!\n";
  return 0;
}
