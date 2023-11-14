#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(5);
	v[1] = 3;
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(2);
	v1[0] = 0;
	v1[1] = 1;
	TDynamicVector<int> v2(v1);
	v1[0] = 1;
	v1[1] = 0;
	EXPECT_EQ(v1[0], 0);
	EXPECT_EQ(v1[1], 1);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);
	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;
	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(7));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	v[3] = 3;
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	ASSERT_NO_THROW(v2 = v1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size_is_correct)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	v2 = v1;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	v1 = v2;
	EXPECT_EQ(v1.size(), 7);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size_is_correct)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	v1 = v2;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (int i = 0; i < 5; i++) {
		v1[i] = i;
		v2[i] = i;
	}
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(5);
	for (int i = 0; i < 5; i++) {
		v[i] = i;
	}
	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 0;
	v[1] = 1;
	v[2] = 2;
	ASSERT_NO_THROW(v + 3);
}

TEST(TDynamicVector, can_add_scalar_to_vector_is_correct)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[0] = 0;
	v1[1] = 1;
	v1[2] = 2;
	v2[0] = 3;
	v2[1] = 4;
	v2[2] = 5;
	v1 = v1 + 3;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 0;
	v[1] = 1;
	v[2] = 2;
	ASSERT_NO_THROW(v - 3);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector_is_correct)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[0] = 0;
	v1[1] = 1;
	v1[2] = 2;
	v2[0] = -3;
	v2[1] = -2;
	v2[2] = -1;
	v1 = v1 - 3;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 0;
	v[1] = 1;
	v[2] = 2;
	ASSERT_NO_THROW(v * 3);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector_is_correct)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[0] = 0;
	v1[1] = 1;
	v1[2] = 2;
	v2[0] = 0;
	v2[1] = 3;
	v2[2] = 6;
	v1 = v1 * 3;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (int i = 0; i < 5; i++) {
		v1[i] = i;
		v2[i] = i + 1;
	}
	ASSERT_NO_THROW(v1 + v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size_is_correct)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	TDynamicVector<int> v3(3);
	for (int i = 0; i < 5; i++) {
		v1[i] = i;
		v2[i] = 2 * i;
		v3[i] = 3 * i;
	}
	EXPECT_EQ(v1 + v2, v3);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (int i = 0; i < 5; i++) {
		v1[i] = i;
		v2[i] = i + 1;
	}
	ASSERT_NO_THROW(v1 - v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size_is_correct)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	TDynamicVector<int> v3(3);
	for (int i = 0; i < 5; i++) {
		v1[i] = 3 * i;
		v2[i] = 2 * i;
		v3[i] = i;
	}
	EXPECT_EQ(v1 - v2, v3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	for (int i = 0; i < 5; i++) {
		v1[i] = i;
		v2[i] = i + 1;
	}
	ASSERT_NO_THROW(v1 * v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size_is_correct)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	int res = 0;
	for (int i = 0; i < 5; i++) {
		v1[i] = 3 * i;
		v2[i] = 2 * i;
		res += 6 * i * i;
	}
	EXPECT_EQ(v1 * v2, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	ASSERT_ANY_THROW(v1 * v2);
}
