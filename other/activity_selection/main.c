#include <stdlib.h>
#include <stdio.h>

#define EDIT_MAX 100

void max_activities(int start[], int finish[], int n) {
    int i, j;
 
    printf ("Following activities are selected \n");
 
    // The first activity always gets selected
    i = 0;
    printf("%d ", i);
 
    // Consider rest of the activities
    for (j = 1; j < n; j++)
    {
      // If this activity has start time greater than or
      // equal to the finish time of previously selected
      // activity, then select it
      if (start[j] >= finish[i])
      {
          printf ("%d ", j);
          i = j;
      }
    }
}
int test_activity_selection() {
    int s[] =  {1, 3, 0, 5, 8, 5};
    int f[] =  {2, 4, 6, 7, 9, 9};
    int n = sizeof(s)/sizeof(s[0]);
    max_activities(s, f, n);
    return 0;
}

int main()
{
    test_activity_selection();
	return 0;
}
