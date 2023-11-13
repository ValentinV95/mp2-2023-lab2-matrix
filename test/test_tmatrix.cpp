#include "tmatrix.h"

#include "gtest.h"

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1;    
	m1[1][0] = 2;
	m1[1][1] = 3;
	TDynamicMatrix<int> m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(2), m2(m1);
	m1[0][0] = 1;
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m1(2);
	EXPECT_EQ(2, m1.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 4;
	EXPECT_EQ(m1[0][0], 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m1(2);
	ASSERT_ANY_THROW(m1.at(-1).at(0) = 4);
	ASSERT_ANY_THROW(m1.at(0).at(-1) = 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m1(2);
	ASSERT_ANY_THROW(m1.at(3).at(0) = 4);
	ASSERT_ANY_THROW(m1.at(0).at(3) = 4);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m1(2);
	ASSERT_NO_THROW(m1 = m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, correct_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1;
	m1[1][1] = 4;
	m2 = m1;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	m1 = m2;
	EXPECT_EQ(m1.size(), 3);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, correct_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	m2[0][0] = 1;
	m2[2][2] = 4;
	m1 = m2;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1;
	m1[1][1] = 4;
	m2[0][0] = 1;
	m2[1][1] = 4;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_unequal_matrices_return_false)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1;
	m2[0][0] = 2;
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(2);
	EXPECT_EQ(m1, m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2), m2(3);
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_multiply_scalar_by_matrix)
{
	TDynamicMatrix<int> m1(2);
	ASSERT_NO_THROW(m1 * 8);
}

TEST(TDynamicMatrix, correct_multiply_scalar_by_matrix)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 2;
	m1[1][1] = 2;
	m1[1][0] = 2;
	m1[0][1] = 2;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) m2[i][j] = 6;
	EXPECT_EQ(m1 * 3, m2);
}

TEST(TDynamicMatrix, can_multiply_vector_by_matrix_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(2);
	ASSERT_NO_THROW(m * v);
}

TEST(TDynamicMatrix, correct_multiply_vector_by_matrix_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(2), res(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
		m[i][j] = 2 * i + j + 1;
	}
	v[0] = 2;
	v[1] = 1;
	res[0] = 4;
	res[1] = 10;
	EXPECT_EQ(m * v,res);
}

TEST(TDynamicMatrix, cant_multiply_vector_by_matrix_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	ASSERT_NO_THROW(m1 + m2);
}

TEST(TDynamicMatrix, correct_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), m3(2);
	m1[0][0] = 1;
	m1[1][1] = 1;
	m2[1][0] = 1;
	m2[0][1] = 1;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) m3[i][j] = 1;
	EXPECT_EQ(m1 + m2, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	ASSERT_NO_THROW(m1 - m2);
}

TEST(TDynamicMatrix, correct_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), m3(2);
	m1[0][0] = 1;
	m1[1][1] = 1;
	m2[1][0] = -1;
	m2[0][1] = -1;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) m3[i][j] = 1;
	EXPECT_EQ(m1 - m2, m3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrixes_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	ASSERT_NO_THROW(m1 * m2);
}

TEST(TDynamicMatrix, correct_multiply_matrixes_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2), m3(2);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
		m1[i][j] = 2 * i + j + 1;
		m2[i][j] = 1;
	}
	m3[0][0] = m3[0][1] = 3;
	m3[1][0] = m3[1][1] = 7;
	EXPECT_EQ(m1 * m2, m3);
}

TEST(TDynamicMatrix, cant_multiply_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);
	ASSERT_ANY_THROW(m1 * m2);
}

