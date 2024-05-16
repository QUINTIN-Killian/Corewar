/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** test_cycle_nb
*/

#include <criterion/criterion.h>

Test(cycle_nb, cycle_an_int)
{
    int ans = cycle_nb(0xffffffff / 2 + 1, 4);

    cr_assert_eq(-(0xffffffff / 2 + 1), ans);
}

Test(cycle_nb, dont_cycle_an_int)
{
    int ans = cycle_nb(0xffffffff / 2, 4);

    cr_assert_eq(0xffffffff / 2, ans);
}

Test(cycle_nb, cycle_a_short)
{
    int ans = cycle_nb(0xffff / 2 + 1, 2);

    cr_assert_eq(-(0xffff / 2 + 1), ans);
}

Test(cycle_nb, dont_cycle_a_byte)
{
    int ans = cycle_nb(127, 4);

    cr_assert_eq(127, ans);
}

Test(cycle_nb, cycle_a_byte)
{
    int ans = cycle_nb(0xff / 2 + 1, 1);

    cr_assert_eq(-(0xff / 2 + 1), ans);
}
