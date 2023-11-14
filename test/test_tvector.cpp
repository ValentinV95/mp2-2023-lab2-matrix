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
    
    TDynamicVector<int> v(3);
    v[0] = 2;
    v[1] = 1;
    v[2] = 0;
    TDynamicVector<int> v1(v);
    ASSERT_EQ(v1, v);
    
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(10);
    TDynamicVector<int> v1(v);
    int* p = &(v[0]);
    int* p1 = &(v1[0]);
    ASSERT_NE(p,p1);
   
}

TEST(TDynamicVector, can_get_size_correct)
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

TEST(TDynamicVector, can_move_vectors_correct) {
    TDynamicVector<int> v(4);
    TDynamicVector<int> v1(5);
    TDynamicVector<int> expect(5);
    expect = v1;
    v = std::move(v1);
    EXPECT_EQ(v, expect);
}
TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v.at(- 1));
    
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v.at(6));
   
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(5);
    ASSERT_NO_THROW(v = v);
    
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    ASSERT_NO_THROW(v = v1);
    
}

TEST(TDynamicVector, assignment_vectors_of_equal_size_is_correct)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    v = v1;
    EXPECT_EQ(v, v1);

}

TEST(TDynamicVector, assign_operator_change_vector_size) 
{
    TDynamicVector<int> v1(5);
    TDynamicVector<int> v2(10);
    v1 = v2;
    EXPECT_EQ(v1.size(), v2.size());
    
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(10);
    ASSERT_NO_THROW(v = v1);
    
}
TEST(TDynamicVector, assignment_vectors_of_different_size_is_correct)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(10);
    v = v1;
    EXPECT_EQ(v, v1);

}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
        v1[i] = i;
    }
    EXPECT_EQ(v,v1);
    
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(5);
    EXPECT_EQ(v, v);
    
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(10);
    EXPECT_NE(v, v1);
    
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    ASSERT_NO_THROW(v+6);

}

TEST(TDynamicVector, addition_scalar_to_vector_is_correct)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
        v1[i] = i+6;
    }
    v = v + 6;
    EXPECT_EQ(v, v1);
    
}
TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    ASSERT_NO_THROW(v-6);

}
TEST(TDynamicVector, subtraction_scalar_from_vector_is_correct)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
        v1[i] = i - 6;
    }
    v = v - 6;
    EXPECT_EQ(v, v1);
    
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    ASSERT_NO_THROW(v*6);


}

TEST(TDynamicVector, multiplication_scalar_by_vector_is_correct)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
        v1[i] = i * 6;
    }
    v = v * 6;
    EXPECT_EQ(v, v1);
   
  
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
        v1[i] = 2 * i;
    }
    ASSERT_NO_THROW(v + v1);

}

TEST(TDynamicVector, additoin_vectors_with_equal_size_is_correct)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    TDynamicVector<int> res(5);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
        v1[i] = 2*i;
        res[i] = 3 * i;
    }
    EXPECT_EQ(v + v1, res);
    
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(10);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        v1[i] = i;
    }
    ASSERT_ANY_THROW(v + v1);
    
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) {
        v[i] = 5 * i;
        v1[i] = 2 * i;
    }
    ASSERT_NO_THROW(v - v1);
}
TEST(TDynamicVector, subtraction_vectors_with_equal_size_is_correct)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    TDynamicVector<int> res(5);
    for (int i = 0; i < 5; i++) {
        v[i] = 5*i;
        v1[i] = 2 * i;
        res[i] = 3 * i;
    }
    EXPECT_EQ(v - v1, res);
    
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(10);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        v1[i] = i;
    }
    ASSERT_ANY_THROW(v - v1);
    
}
TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{

    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    for (int i = 0; i < 5; i++) {
        v[i] = 3 * i;
        v1[i] = 2 * i;
    }
    ASSERT_NO_THROW(v * v1);

}
TEST(TDynamicVector, multiplication_vectors_with_equal_size_is_correct)
{

    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(5);
    int res=0;
    for (int i = 0; i < 5; i++) {
        v[i] = 3 * i;
        v1[i] = 2 * i;
        res += 6 * i*i;
    }
    EXPECT_EQ(v * v1, res);
    
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v(5);
    TDynamicVector<int> v1(10);
    for (int i = 0; i < 5; i++) {
        v[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        v1[i] = i;
    }
    ASSERT_ANY_THROW(v * v1);
    
}

