#include <stdio.h>
#include <stdlib.h>
#include "master_ceng.h"
#include "master_ceng.c"
int main(int argc, char const *argv[])
{
    Instructor *instructors = NULL;
    Submission *submissions = NULL;
    Score *scores, best;
    int i, j, jury_size = 3;
    float avg_score;

    char instructor_names[4][10] = {"Sengor", "Hande", "Ahmet", "Tolga"};
    char student_names[3][10] = {"Emre", "Gorkem", "Yusuf"};
    float instructor_pls[4][4] = {
        {5.0, 4.2, 2.3, 3.1},
        {2.1, 3.4, 4.2, 5.0},
        {3.1, 5.0, 4.5, 2.3},
        {3.2, 4.2, 1.3, 4.6}};
    int submission_pls[3][5] = {
        {0, 1, 0, 2, 1},
        {1, 2, 3, 0, 0},
        {2, 2, 3, 3, 1}};
    int jury_indexes[3][3] = {
        {0, 1, 2},
        {0, 2, 3},
        {1, 2, 3}};

    int **juries = (int **)malloc(sizeof(int *) * 3);

    /* create jury indexes */
    for (i = 0; i < 3; i++)
    {
        juries[i] = (int *)malloc(sizeof(int) * jury_size);
        for (j = 0; j < jury_size; j++)
        {
            juries[i][j] = jury_indexes[i][j];
        }
    }

    /* create instructors */
    for (i = 0; i < 4; i++)
    {
        insert_instructor(&instructors, instructor_names[i], instructor_pls[i]);
    }
    print_instructor(instructors);

    /* create submissions */
    for (i = 0; i < 3; i++)
    {
        insert_submission(&submissions, student_names[i], submission_pls[i]);
    }
    print_submission(submissions);

    scores = calculate_submission_scores(instructors, submissions, juries, jury_size);
    print_scores(submissions, scores);

    avg_score = find_average_score(scores, submissions);
    printf("Average score: %.2f\n", avg_score);

    best = find_winner(scores, submissions);
    printf("Best student: %s, Max Score: %.2f\n", best.student_name, best.score);

    return 0;
}
