#include <stdio.h>
#include <stdlib.h>
#include "master_ceng.h"

char pl_names[4][10] = {
    "C",
    "C++",
    "Python",
    "Java"};

struct Submission* sub_node_maker(char *name, int *pl_list){
    int i = 0,j =0 ;
    struct Submission* sub_node_p;
    sub_node_p = (Submission*)malloc(sizeof(Submission));
    sub_node_p->student_name = (char*)malloc(sizeof(char)*10);
    sub_node_p->projects = (Project*)malloc(sizeof(Project)*5);
    if(sub_node_p){
      while(name[i] != '\0'){
          
            sub_node_p->student_name[i] = name[i];
            i += 1;
            
            
      }
      sub_node_p->student_name[i] = '\0';
      
      while(j < 5){
          sub_node_p->projects[j].project_index = (char)j;
          if(pl_list[j] == 0){
          sub_node_p->projects[j].pl_index = 0;
          }
          else if (pl_list[j] == 1){
          sub_node_p->projects[j].pl_index = 1;
          }
          else if (pl_list[j] == 2){
          sub_node_p->projects[j].pl_index = 2;
          }
          else if (pl_list[j] == 3){
          sub_node_p->projects[j].pl_index = 3;
          }
            j +=1;               
        }
    }
    return sub_node_p;
}

struct Instructor* inst_node_maker(char *name, float *pl_ratings){
    int i = 0, j =0;
    struct Instructor* inst_node_p;
    inst_node_p = (Instructor*)malloc(sizeof(Instructor));
    inst_node_p->instructor_name = (char*)malloc(sizeof(char)*10);
    inst_node_p->pl_ratings = (float*)malloc(sizeof(float)*4);
    if (inst_node_p){
        while(name[i] != '\0'){
            inst_node_p->instructor_name[i] = name[i]; 
            i += 1;
        }
        inst_node_p->instructor_name[i] = name[i];
        while(j < 4){
            inst_node_p->pl_ratings[j] = pl_ratings[j];
            j += 1;
        }
        
        inst_node_p->next = NULL;
    }
    return inst_node_p;
}
/*
Takes Instructors' linked list, name of the instructor and pl_ratings array
*/
void insert_instructor(Instructor **list, char *name, float *pl_ratings)
{   
    struct Instructor* instructors;
    struct Instructor *curr, *prev;
    instructors = inst_node_maker(name, pl_ratings);
    if(instructors){
        
        curr = *list;
        prev = NULL;
        while(curr){
            prev = curr;
            curr = curr->next;
            
        }
        instructors->next = curr;
        if(prev){
            prev->next = instructors;
        }
        else{
            *list = instructors;
        }
    }
    
}

/*
Takes Submissions' linked list, name of the student and pl indexes of projects
*/
void insert_submission(Submission **list, char *name, int *pl_list)
{
    
    struct Submission* submissions;
    struct Submission *curr, *prev;
    submissions = sub_node_maker(name, pl_list);
    if(submissions){
        
        curr = *list;
        prev = NULL;
        while(curr){
            prev = curr;
            curr = curr->next;
            
        }
        submissions->next = curr;
        if(prev){
            prev->next = submissions;
        }
        else{
            *list = submissions;
        }
    }
    
}

/*
Takes Instructor linked list, Submission linked list, 
jury member indexes for each submission, number of jury members for each submission

return: Array of Score structure
*/
Score *calculate_submission_scores(Instructor *instructions, Submission *submissions, int **juries, int jury_size)
{   int i , j , l, a, count ;
    struct Submission *temp_sub;
    struct Instructor *temp_inst;
    struct Score *score_array;
    
    temp_sub = submissions;
    temp_inst = instructions;
    count = 0;
    while(temp_sub != NULL){
        count = count + 1;
        temp_sub = temp_sub->next;
    }
    
    temp_sub = submissions;
    score_array = (Score*)malloc(sizeof(Score)*count);
    
    
    for (i = 0; i < count; i++){
        score_array[i].student_name = (char*)malloc(sizeof(char)*10);
        score_array[i].student_name = temp_sub->student_name;
        
        temp_sub = temp_sub->next;
    }
    
    temp_sub = submissions;
    
    for(i = 0; i < count; i++,temp_sub = temp_sub->next){
        score_array[i].score = 0;
        for(j = 0; j<5; j++){
            
                for(l = 0; l< jury_size; l++, temp_inst = instructions){
                    for(a=0 ; a != juries[i][l]; a++){
                        temp_inst = temp_inst->next;
                    }
                if(temp_sub->projects[j].pl_index == 0){
                    score_array[i].score += temp_inst->pl_ratings[0];
                } 
                else if(temp_sub->projects[j].pl_index == 1){
                    score_array[i].score += temp_inst->pl_ratings[1];
                }
                else if(temp_sub->projects[j].pl_index == 2){
                    score_array[i].score += temp_inst->pl_ratings[2];
                } 
                else if(temp_sub->projects[j].pl_index == 3){
                    score_array[i].score += temp_inst->pl_ratings[3];
                }
                
            }
            
        }
       
} 
    
    return score_array;
 
}
/*
Takes scores and size of scores as input. Finds and returns average of the scores.

return: average score of submissions
*/
float find_average_score(Score *scores, Submission *submissions)
{   int i , count = 0;
    float total, avg;
    total = 0; 
    while(submissions != NULL){
        count += 1;
        submissions = submissions->next;
    }
    
    for(i =0; i < count; i++){
        total += scores[i].score;
    }
    avg = total/count;
    
    return avg;
}

/*
Takes submissions and scores as input. Finds and returns corresponding Score instance of winner.

return: Score instance of best submission 
*/
Score find_winner(Score *scores, Submission *submissions)
{   
    int i =0 , j, count, index;
    float max =0;
    Score winner;
    struct Submission* temp_sub;
    temp_sub = submissions;
    while(temp_sub != NULL){
        count += 1;
        temp_sub = temp_sub->next;
    }
        index = 0;
        max = scores[0].score;
        for(i = 0; i < count; i++,j++){
            for(j = 1; j < count; j++){
                if(max < scores[j].score){
                    max = scores[j].score;
                    index = j;
                }
            }
        }
    
    winner.student_name = scores[index].student_name;
    winner.score = max;
    return winner;
}

/*
Prints instructors' linked list.
*/
void print_instructor(Instructor *instructors)
{   
    int i =0, j=0;
    struct Instructor* temp_inst;
    temp_inst = instructors;
    while(temp_inst){
        printf("Name: ");
        while(temp_inst->instructor_name[i] != '\0'){
            printf("%c", temp_inst->instructor_name[i]);
            i += 1;
        }
        i = 0;
        printf("\n");
        printf("Ratings: ");
        while(j<4){
            if(j<3){
                printf("%.2f ", temp_inst->pl_ratings[j]);
            }
            else{
                printf("%.2f", temp_inst->pl_ratings[j]);
            }    
            j += 1;
        }
        printf("\n");
        j = 0;
        temp_inst = temp_inst->next;
    } 
    
    
}

/*
Prints submissions' linked list.
*/
void print_submission(Submission *submissions)
{
    /* write your code here */
    int i = 0, j=0;
    struct Submission* temp_sub;
    temp_sub = submissions;
    while(temp_sub){
        printf("Name: " );
        while(temp_sub->student_name[i] != '\0'){
            printf("%c", temp_sub->student_name[i]);
            i += 1;
    }
            i = 0;
        printf("\n");
        while(j < 5){
            if(temp_sub->projects[j].pl_index == 0){
                printf(" Project-%d: ", j+1);
                printf("C");
                printf("\n");
            }
            else if(temp_sub->projects[j].pl_index == 1){
                printf(" Project-%d: ", j+1);
                printf("C++");
                printf("\n");
            }
            else if(temp_sub->projects[j].pl_index == 2){
                printf(" Project-%d: ", j+1);
                printf("Python");
                printf("\n");
            }
            else if(temp_sub->projects[j].pl_index == 3){
                printf(" Project-%d: ", j+1);
                printf("Java");
                printf("\n");
            } 
            j += 1;
    }    
        j = 0;
        temp_sub = temp_sub->next;
}
}
/*
Prints array of Score structure.
*/
void print_scores(Submission *submissions, Score *scores)
{   int i, j, count = 0;
    struct Submission * temp_sub;
    temp_sub = submissions;
    while(temp_sub != NULL){
        count = count + 1;
        temp_sub = temp_sub->next;
    }
    for(i = 0; i < count; i++){
        printf("Score of ");
        for(j = 0; scores[i].student_name[j] != '\0'; j++){
            printf("%c", scores[i].student_name[j]);
        }
        printf(": %.2f\n", scores[i].score);
    }
    
    
    
}

