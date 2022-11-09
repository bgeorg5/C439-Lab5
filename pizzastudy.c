#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>

/*Global Variables*/
bool ordered = false;
int Max = 13;
int numPizzas = 0;
sem_t sem_p, sem_c;

struct Pizza{
int slices;
};
struct Pizza p;

/*Producer*/
void *producer(void *param){
while(numPizzas < Max){
	while(ordered == true){
	sleep(1);
	
	sem_wait(&sem_c);
	
	p.slices = 8;
	numPizzas++;
	printf("Pizza %d is deliivered \n", numPizzas);
	
	sem_post(&sem_c);
	sem_post(&sem_p);
	
	ordered = false;

	}
}
	
return NULL;

}

/*Consumer*/
void *consumer(void *args){
int num = *((int *) args);

	while(numPizzas <= Max){
	sleep(1);
	sem_wait(&sem_c);
		
		/*Order*/
		if(p.slices <= 0 && ordered == false && numPizzas < Max){
		sem_wait(&sem_p);
			printf("Student %d orders pizza %d \n", num, numPizzas+1);
			ordered = true;
		}
		
		/*Consume*/
		if(p.slices > 0){
			printf("Student %d eats slice %d from pizza %d \n", num, p.slices, numPizzas);
			p.slices--;
		}
		
	sem_post(&sem_c);
	}
	
return NULL;

}

int main(){

	sem_init(&sem_c, 0,1);
	sem_init(&sem_p, 0,1);
	int total_students;
	p.slices = 0;

	printf("please enter the number of students (2-5): \n");
	scanf("%d", &total_students);
	pthread_t s[total_students], prod;
	int sid[total_students];
		
		/*Initialize student id numbers*/
		for(int i = 1; i <= total_students; i++){
			sid[i-1] = i;
		}

		/*Initialize Threads*/
		pthread_create(&prod, NULL, producer, NULL);
		for(int i = 0; i < total_students; i++){
			pthread_create(&s[i], NULL, consumer, &sid[i]);

		}
		
		/*Join Threads*/
		pthread_join(prod, NULL);
		for(int i = 0; i < total_students-1; i++){
			pthread_join(s[i], NULL);
		}

	return 0;

}

