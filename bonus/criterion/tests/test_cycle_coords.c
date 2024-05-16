/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** test_cycle_coords
*/

#include <criterion/criterion.h>

Test(cycle_coords, classic_cycle_coords_positive)
{
    int ans = cycle_coords(6 * 1024);

    cr_assert_eq(ans, 0);
}

Test(cycle_coords, doucle_cycle_coords_positive)
{
    int ans = cycle_coords(6 * 1024 + 2);

    cr_assert_eq(ans, 2);
}

Test(cycle_coords, a_lot_cycle_coords_positive)
{
    int ans = cycle_coords((6 * 1024) * 2 + 5);

    cr_assert_eq(ans, 5);
}

Test(cycle_coords, classic_cycle_coords_negative)
{
    int ans = cycle_coords(-1);

    cr_assert_eq(ans, 6 * 1024 - 1);
}
