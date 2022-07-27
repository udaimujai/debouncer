#include <unity.h>
#include<debouncer.h>
#include "bsp.h"
void test_debouncer_init ()

{
    
    //debouncer_init should be called before calling debouncer_get_state. else return error.
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_NOT_INITIALIZED,  debouncer_get_state(0));

    // if NULL is sent the return error.
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_INVALID_PIN_ARRAY, debouncer_init(NULL, 2));
   
   //if out of range numbers are sent return error.
    uint8_t pins_out_of_range_count[] = {1,2,3,4,5,6,7,8,9};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_BUTTONS_TOO_MANY, debouncer_init(pins_out_of_range_count,sizeof(pins_out_of_range_count)));
    
    //if repeated buttons are sent return error.
    uint8_t pins_repeated[] = {1,2,3,4,5,6,7,7};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_DUPLICATED, debouncer_init(pins_repeated, sizeof(pins_repeated)));
    
    //if button number is too big then return error.
    uint8_t pins_out_of_range[] = {1,2,3,4,157,6};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_PIN_OUT_OF_RANGE, debouncer_init(pins_out_of_range, sizeof(pins_out_of_range)));
    
    //
    uint8_t pins_OK[] = {1,2,3,4,5,6,7,8};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_NO_ERROR, debouncer_init(pins_OK, sizeof(pins_OK)));
    for(int i = 0; i == 8; i++)
    {
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(i));
    }




}
void test_debouncer_states()
{
    uint8_t pins_OK[] = {33};
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_NO_ERROR, debouncer_init(pins_OK, sizeof(pins_OK)));
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_ERROR_PIN_NOT_FOUND, debouncer_get_state(40));
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(33));
    bsp_set_fake_val(0);
    debouncer_update(); //1
    debouncer_update(); //2
    debouncer_update(); //3
    debouncer_update(); //4
    bsp_set_fake_val(1);
    debouncer_update(); // reset

    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(33));

    bsp_set_fake_val(0);
    debouncer_update(); //1
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(33));

    debouncer_update(); //2
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(33));

    debouncer_update(); //3
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(33));

    debouncer_update(); //4
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(33));

    debouncer_update(); //5
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_FALLING, debouncer_get_edge(33));
    
    debouncer_update(); //5
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_state(33));

    //State Change to High
    bsp_set_fake_val(1);
    debouncer_update(); //1
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_state(33));

    debouncer_update(); //2
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_state(33));

    debouncer_update(); //3
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_state(33));

    debouncer_update(); //4
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_LOW, debouncer_get_state(33));

    debouncer_update(); //5
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_RISING, debouncer_get_edge(33));
    
   // debouncer_update(); //6
    TEST_ASSERT_EQUAL_UINT8(DEBOUNCER_STATE_HIGH, debouncer_get_state(33));
}
int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_debouncer_init);
    RUN_TEST(test_debouncer_states);
    return 0;
}