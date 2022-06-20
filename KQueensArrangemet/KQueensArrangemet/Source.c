#include <stdio.h>
#include <stdlib.h>

struct point
{
    int x;
    int y;
};

int n, m, positions_count;

int is_avaiable(struct point target_cell, int* available_cells)
{
    return available_cells[n * target_cell.x + target_cell.y] == 0;
}

void remove_cell(struct point target_cell, int* available_cells)
{
    available_cells[n * target_cell.x + target_cell.y] = -1;
}

void put_queen(int row, int* available_cells)
{
    int i, j, pos;
    struct point current_cell, temp_cell;
    int* available_cells2;
    available_cells2 = (int*)malloc(m * sizeof(int));
    current_cell.x = row;
    for (int column = 0; column < n; column++)
    {
        current_cell.y = column;
        if (is_avaiable(current_cell, available_cells))
            if (row == n - 1) positions_count++;
            else
            {
                for (int k = 0; k < m; k++) {
                    available_cells2[k] = available_cells[k];
                }
                temp_cell.y = column;
                for (i = row; i < n; i++)
                {
                    temp_cell.x = i;
                    remove_cell(temp_cell, available_cells2);
                }
                for (i = row, j = column; (i < n) && (j > -1); i++, j--)
                {
                    temp_cell.x = i;
                    temp_cell.y = j;
                    remove_cell(temp_cell, available_cells2);
                }
                for (i = row, j = column; (i < n) && (j < n); i++, j++)
                {
                    temp_cell.x = i;
                    temp_cell.y = j;
                    remove_cell(temp_cell, available_cells2);
                }
                put_queen(row + 1, available_cells2);
            }
    }
    free(available_cells2);
}

int count_positions()
{
    int i, j, k;
    int* available_cells;
    m = n * n;
    available_cells = (int*)malloc(m * sizeof(int));
    k = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            available_cells[k] = 0;
            k++;
        }
    positions_count = 0;
    put_queen(0, available_cells);
    free(available_cells);
    return positions_count;
}

int main()
{
    scanf_s("%d", &n);
    printf("The number of arrangements: %d", count_positions());
    return 0;
}