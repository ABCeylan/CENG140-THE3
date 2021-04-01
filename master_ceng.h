#ifndef __MASTER_CENG__H__
#define __MASTER_CENG__H__

struct Instructor
{
    float *pl_ratings;
    char *instructor_name;
    struct Instructor *next;
};
typedef struct Instructor Instructor;

struct Project
{
    int pl_index;
    char project_index;
};
typedef struct Project Project;

struct Submission
{
    Project *projects;
    char *student_name;
    struct Submission *next;
};
typedef struct Submission Submission;

struct Score
{
    char *student_name;
    float score;
};
typedef struct Score Score;

/*
Takes Instructors' linked list, name of the instructor and pl_ratings array
*/
void insert_instructor(Instructor **list, char *name, float *pl_ratings);

/*
Takes Submissions' linked list, name of the student and pl indexes of projects
*/
void insert_submission(Submission **list, char *name, int *pl_list);

/*
Takes Instructor linked list, Submission linked list, 
jury member indexes for each submission, number of jury members for each submission

return: Array of Score structure
*/
Score *calculate_submission_scores(Instructor *instructions, Submission *submissions, int **juries, int jury_size);

/*
Takes scores and size of scores as input. Finds and returns average of the scores.

return: average score of submissions
*/
float find_average_score(Score *scores, Submission *submissions);

/*
Takes submissions and scores as input. Finds and returns corresponding Score instance of winner.

return: Score instance of best submission 
*/
Score find_winner(Score *scores, Submission *submissions);

/*
Prints instructors' linked list.
*/
void print_instructor(Instructor *instructors);

/*
Prints submissions' linked list.
*/
void print_submission(Submission *submissions);

/*
Prints array of Score structure.
*/
void print_scores(Submission *submissions, Score *scores);

#endif
