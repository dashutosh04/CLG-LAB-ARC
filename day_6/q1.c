#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct p_t
{
    int id;
    char *name;
    int age;
    int h;
    int w;
};

struct p_t *p = NULL;
int n = 0;
int min_h = 0;
int max_h = 0;

void swap(struct p_t *a, struct p_t *b)
{
    struct p_t temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(int size, int i)
{
    int s = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && p[l].age < p[s].age)
    {
        s = l;
    };
    if (r < size && p[r].age < p[s].age)
    {
        s = r;
    };

    if (s != i)
    {
        swap(&p[i], &p[s]);
        min_heapify(size, s);
    }
}

void build_min_h()
{
    if (n == 0)
    {
        printf("No data. Read data first.\n");
        return;
    }
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        min_heapify(n, i);
    }
    min_h = 1;
    max_h = 0;
    printf("Min-heap (age) created.\n");
}

void max_heapify(int size, int i)
{
    int lrg = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < size && p[l].w > p[lrg].w)
        lrg = l;
    if (r < size && p[r].w > p[lrg].w)
        lrg = r;

    if (lrg != i)
    {
        swap(&p[i], &p[lrg]);
        max_heapify(size, lrg);
    }
}

void build_max_h()
{
    if (n == 0)
    {
        printf("No data. Read data first.\n");
        return;
    }
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        max_heapify(n, i);
    }
    max_h = 1;
    min_h = 0;
    printf("Max-heap (weight) created.\n");
}

void cleanup()
{
    if (p != NULL)
    {
        for (int i = 0; i < n; i++)
            free(p[i].name);
        free(p);
        p = NULL;
    }
}

void read_data()
{
    FILE *fp = fopen("person_data.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening person_data.txt\n");
        return;
    }

    cleanup();
    n = 0;
    int cap = 10;
    p = (struct p_t *)malloc(cap * sizeof(struct p_t));
    if (p == NULL)
    {
        printf("Malloc failed!\n");
        fclose(fp);
        return;
    }

    char buf[100];
    while (fscanf(fp, "%d %s %d %d %d", &p[n].id, buf, &p[n].age, &p[n].h, &p[n].w) == 5)
    {
        p[n].name = strdup(buf);
        n++;
        if (n == cap)
        {
            cap *= 2;
            struct p_t *tmp = realloc(p, cap * sizeof(struct p_t));
            if (tmp == NULL)
            {
                printf("Realloc failed!\n");
                cleanup();
                fclose(fp);
                return;
            }
            p = tmp;
        }
    }
    fclose(fp);
    printf("%d records read.\n", n);
}

void disp_young()
{
    if (!min_h)
    {
        printf("Create Min-heap (age) first.\n");
        return;
    }
    if (n > 0)
    {
        printf("Youngest person (Age: %d) weight: %d\n", p[0].age, p[0].w);
    }
    else
    {
        printf("Heap is empty.\n");
    }
}

void insert()
{
    if (!min_h)
    {
        printf("Create Min-heap (age) first.\n");
        return;
    }
    struct p_t np;
    char buf[100];
    printf("Enter (ID Name Age Height Weight): ");
    scanf("%d %s %d %d %d", &np.id, buf, &np.age, &np.h, &np.w);
    np.name = strdup(buf);
    n++;
    p = (struct p_t *)realloc(p, n * sizeof(struct p_t));
    if (p == NULL)
    {
        printf("Realloc failed on insert!\n");
        n--;
        return;
    }
    int i = n - 1;
    p[i] = np;
    while (i != 0 && p[(i - 1) / 2].age > p[i].age)
    {
        swap(&p[i], &p[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    printf("New person inserted.\n");
}

void del_old()
{
    if (!min_h)
    {
        printf("Create Min-heap (age) first.\n");
        return;
    }
    if (n == 0)
    {
        printf("Heap empty.\n");
        return;
    }
    int old_a = -1, old_i = -1;
    for (int i = n / 2; i < n; i++)
    {
        if (p[i].age > old_a)
        {
            old_a = p[i].age;
            old_i = i;
        }
    }
    if (old_i == -1)
        old_i = (n > 0) ? 0 : -1;
    if (old_i == -1)
    {
        printf("Cannot find oldest person.\n");
        return;
    }
    printf("Deleting oldest: %s (Age: %d)\n", p[old_i].name, p[old_i].age);
    free(p[old_i].name);
    p[old_i] = p[n - 1];
    n--;
    p = (struct p_t *)realloc(p, n * sizeof(struct p_t));
    build_min_h();
    printf("Oldest person deleted. Heap rebuilt.\n");
}

int main()
{
    int ch;
    while (1)
    {
        printf("\nMENU\n1.Read 2.Min-Heap(age) 3.Max-Heap(weight) 4.Youngest's Wt 5.Insert 6.Del Oldest 7.Exit\n> ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            read_data();
            break;
        case 2:
            build_min_h();
            break;
        case 3:
            build_max_h();
            break;
        case 4:
            disp_young();
            break;
        case 5:
            insert();
            break;
        case 6:
            del_old();
            break;
        case 7:
            cleanup();
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}
