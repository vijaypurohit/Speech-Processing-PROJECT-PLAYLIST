/******************************************************************************************************************************************
	Speech Processing CS 566: PROJECT (SPEECH BASED PLAYLIST)
	Roll No: 214101058 MTech CSE'23 IITG
	Input: 
		*	input_lamda/* 		= Contains: PRESENTLY USED "Lamda Model for Each Digit"
			**	      		= Contains: Generated "Universe.csv" of Cepstral Coefficients of Training Files
			**	      		= Contains: "Codebook" file to be read.
		*	input_live_voice_data/*	= Contains: Live Recording Files, 
							Their Observation Sequences, 
							Their Test Result Using Model (default model or newly converged model)
						 (Can Clean These Files Except the Folders Present)
			**	input_live_voice_data/TRAINING	= Contains Digits Recordings generated Using Application for Training Purpose 
			**	input_live_voice_data/TESTING	= Contains: Digits Recordings generated Using Application for Testing Purpose
			*** 	in the end, replace appropriately using menu. (Why replace utterance files? bec default folder for observation seq is input_voice)
					input_live_voice_data/TRAINING/* --> input_voice_training_data/*
					input_live_voice_data/TESTING/* --> input_voice_testing_data/*
		*	input_voice_training_data/*	= Contains: Training Utterance Recordings for Input into model
		*	input_voice_testing_data/*	= Contains: Test Utterance Recordings for Input into model
		* 	RecordingModule/*		= Contains: Recording Module Files
		* 	SONGS/*				= Contains: SONGS for each language (to be uploaded manually by user in their respective folder)

	Output:  
		*	output/*		= Contains:	Result Analysis of Converged Model for Each Digit.
			**	output/Models/*	= Contains: 	Newly Generated Model using Input Trainning Files provided.
		*	output_voice_recordings_analysis_files	= Contains: Recording Analysis files which 
								shows Frames used, Samples used, STE Marker, Cepstral Coefficients etc
								For Files of Input Training, Input Testing, Live Recordings
		*	output_voice_recordings_normalised_segregated	= Contains: Segragated Speech Part using Start and End Marker
								For Files of Input Training, Input Testing, Live Recordings
	Debug Variables:	
		* 	segregate_speech :	True: to segreagate speech data with respect to start and end marker in its output folder (output_voice_recordings_normalised_segregated). 
		*	segregate_Live_speech :	True: to segreagate Live Recording data with respect to start and end marker in its output folder (output_voice_recordings_normalised_segregated). 
		*	showCoefficientsInFile :	True: show Coefficients Values R, A, C's of each frames in its analysised files (output_voice_recordings_analysis_files).
		*	showAlphaBetaPstarInConsole :	True: to show alpa, beta probabilities in the console for each observation sequence. (also saved in files in (output/) )
		*	showStateSeqAlphaBetaInFileForEachObsAfterConverge :	True: It will save each utterance alpha, beta probabilites and state sequence in the file in (output/).

*********************************************************************************************************************************************/


#include "stdafx.h"
#pragma warning (disable : 4996)		//to disable fopen() warnings
#include <stdio.h>
#include <stdlib.h>		//atoi, atof
#include <string.h>		//strcpy
#include <conio.h>		//getch,
#include <time.h>		// time(NULL)
#define _USE_MATH_DEFINES	// for pi
#include <math.h>       // abs, log, sin, floor
#include <windows.h>	
#include <direct.h>		//_mkdir
#pragma comment(lib,"Winmm.lib")	// lib for listenning to sound

/******************--------Common Settings--------******************/
#define p 12						 //	Number of Cepstral Coefficients, dimensionality of vector x
//#define codeBkSize 32		//change // CodeBook Y Size = K = M		
//#define distr_delta 0.000001			 // 0.00001 or 0.000001 abs(old_distortion - new_dist) > delta. 
#define W 8				//change //  Default Number of Words/Digits//HMM
#define Wmax 20				//change //  Max Number of Words/Digits//HMM
#define N 5					//change // Number of States per HMM
#define M 32				//change // Number of Distinct Observation Symbols
#define Tmax 150			//change // Max Length of Observation Sequence
#define On 20				//change // Number of Training Observations Given for one Word
#define Ot 10				//change // Number of Testing Observations Given for one Word
#define model_iterations 200				//change // Number of times Re-estimation has to be done
#define repeatConvergence 2		// second time use converged model to converge again

#define TRAINING 1
#define TESTING 2
#define LIVETRAINING 3
#define LIVETESTING 4
#define InputFolderModel 1
#define OutputFolderModel 2

//------------------------------------------------- DEBUG PURPOSE ----------------------------------------------------------------
bool segregate_speech = true;			// True: to segreagate speech data with respect to start and end marker in its output folder. 
bool segregate_Live_speech = true;
bool showCoefficientsInFile = false;		// True: Show Coefficients Values R, A, C's in each voice analysised files
bool showAlphaBetaPstarInConsole = false;	//True: to show alpa, beta probabilities in the console for each observation sequence
bool showStateSeqAlphaBetaInFileForEachObsAfterConverge = true;

//----------------------------------------------------------------  ----------------------------------------------------------------
/******************--------Variable Decalaration--------******************/
// HMM Lamda
long double PI[N];			// Initial State Distribution
long double A[N][N];		// State Transition Probability Distribution
long double B[N][M];		// Observation Symbol Probability Distribution						// 
int O[On>Ot?On:Ot][Tmax];			// N observation Sequence Length of T (for training, testing), Observation Sequence Given, Codebook Index Entry
int OFmax[On>Ot?On:Ot];				// max frames in each observation sequence
int offline_correct_count=0;	// to detect number of utterance of Word correctly recognized
int offline_overall_count=0;	// to detect number of utterance of Word correctly recognized in all files

// P1 Evaluation Problem (Scoring Problem)
long double alpha[Tmax][N]; // T*N, forward procedure variable, Prob of Partial Observation Seq O1 to Ot until time t and state Si  at time t given model lambda
long double beta[Tmax][N];  // T*N, backward procedure variable, Prob of Partial Obser Seq O(t+1) to Ot given state Si at time t and mdodel lamda
long double probability_alpha, probability_beta;

// P2 Uncovering the Problem
long double gamma[Tmax][N]; // T*N, Prob of being in state Si at time t given the Obser Seq and model lamda
long double delta[Tmax][N]; // T*N, Viterbi Algo variable, best score along a single path, at time t which accounts for the first t obser and ends in state Si
int psi[Tmax][N];   // T, Viterbi Algo variable, Book Keeping Var to keep track of argument that maximized the delta
long double Pstar, Pstar_old;	 // Viterbi Algo variable, max probability of delta_T_i 
int Qstar[Tmax];	 // Viterbi Algo variable, State Sequence path

// P3 Reestimation Problem
long double XI[Tmax][N][N];		// Xai Matrix
long double PI_BAR[N];			// Re-estimated Initial State Distribution
long double A_BAR[N][N];		// Re-estimated State Transition Probability Distribution
long double B_BAR[N][M];		// Re-estimated Observation Symbol Probability Distribution
long double converged_A[On][N][N];		// save all the converged A matrix of training Sequence
long double converged_B[On][N][M];		// save all the converged B matrix of training sequence			
long double A_Prev[N][N];		// Previous Averaged A Matrix
long double B_Prev[N][M];		// Previous Averaged B Matrix

// CodeBook
long double codebook[M][p];
const char codebook_file_name[] = "codebook_fb.txt";
bool codebook_universe_generation = false;
// Files								
const char input_folder[] = "input_lamda/";
const char output_folder[] = "output/";
//const char WordFolderName[] = "Word";
const char *LambdaFileNames[] = {"A_","B_","Pi_","obs_seq_training_", "obs_seq_testing_"};
//const char *WordNames[]={"0","1","2","3","4","5","6","7","8","9"};
const char voice_data_prefix[] = "obs_";
const char output_folder_Model_name[] = "Models";
const char word_file_name[] = "words.txt";

//WORDS
//char *HMM_WORDS[]={"Digit_0","Digit_1","Digit_2","Digit_3","Digit_4","Digit_5","Digit_6","Digit_7","Digit_8","Digit_9"};;
const int num_of_char_per_line=101;
char *HMM_WORDS[Wmax];
int totWords=W;

//PLAYLIST
int lang_index_begin=5;		// Songs Words Start from which index
// max 20 lang, per lang 5 songs, 100 char each song
const int max_Songs=5;
char *playlist_songs_arr[Wmax][max_Songs];

//char *playlist_english[] = {
//		"Alec Benjamin - Let Me Down Slowly",
//		"Duncan Laurence - Arcade",
//		"Ed Sheeran - Shape of You",
//		"Ellie Goulding - Love Me Like You Do - From Fifty Shades Of Grey",
//		"The Kid Laroi, Justin Bieber - STAY"
//};
//
//char *playlist_hindi[] = {
//		"Adnan Sami - Tera_Chehra",
//		"Bar Bar Dekho - Kho Gaye Hum Kahan",
//		"Call - Laaree Chootee",
//		"JalRaj - Gulabi Aankhen Jo Teri Dekhi (Reprise)",
//		"Sonu Ke Titu Ki Sweety - Tera Yaar Hoon Main"
//};


FILE *fp_console ;		//to write output file		
char completePathOuput[200];

// Observation Sequence Generations Functions	
#include "observation_sequence.h"

// hmm functions	
#include "hmm_solutions.h"
#include "hmm_record.h"
#include "hmm_testing.h"
#include "hmm_playlist.h"
/**************************************************************************************
	To Display Common Settings used in our System
	Input: File Pointer in case things needed to be written on file.
**************************************************************************************/
void DisplayCommonSettings(FILE *fp_set=NULL){
	// General Information to Display
	if(fp_set==NULL){
		printf("****-------- WELCOME TO HMM --------****\n");		
		printf("-Common Settings are : -\n");	
		printf(" P (=Q)(#of Cepstral Coefficients) : %d\n", p);
		printf(" Number of Words/Digits/HMM (totWords) : %d\n", totWords);	
		printf(" Number of States per HMM (N) : %d\n", N);	
		printf(" Number of Distinct Observation Symbols (M) or CodeBook Size (Y) : %d\n", M); 	
		printf(" Max Length of Observation Sequence (T) : %d\n", Tmax);			
		printf(" Number of Training Observations : %d\n", On);	
		printf(" Number of Testing Observations : %d\n", Ot);

		printf("\n");
		printf(" Frame Size : %d\n", sizeFrame);	
		printf(" Tokhura Weights : ");
		for(int i=0; i<q; i++){
			printf("%0.1f(%d) ", w_tkh[i],i+1);
		}
		printf("\n Amplitutde Value to Scale : %d\n", scaleAmp);			
		printf(" Intital Header Lines Ignore Count : %d\n", initIgnoreHeaderLines); 
		printf(" Intital Samples to Ignore : %d\n",initIgnoreSamples);	
		printf(" Intital Noise Frames Count : %d\n",initNoiseFrames);	
		printf(" Noise to Energy Factor : %d\n",thresholdNoiseToEnergyFactor); 
		printf(" Sampling Rate of Recording: %d\n",samplingRate); 

		printf("\n =>Total Words in HMM:: %d\n",totWords);
		for(int w=0; w<totWords ;w++)
		{
			printf(" -->W[%d]:[%s]\n",w,HMM_WORDS[w]);
		}
		printf("----------------------------------------------------------------\n\n");	
	}
	else{
		//printing in file
		fprintf(fp_console,"****-------- WELCOME TO HMM --------****\n");		
		fprintf(fp_console,"-Common Settings are : -\n");	
		fprintf(fp_console," P (=Q)(#of Cepstral Coefficients) : %d\n", p);
		fprintf(fp_console," Number of Words/Digits/HMM (totWords) : %d\n", totWords);	
		fprintf(fp_console," Number of States per HMM (N) : %d\n", N);	
		fprintf(fp_console," Number of Distinct Observation Symbols (M) or CodeBook Size (Y) : %d\n", M); 	
		fprintf(fp_console," Max Length of Observation Sequence (T) : %d\n", Tmax);			
		fprintf(fp_console," Number of Training Observations : %d\n", On);	
		fprintf(fp_console," Number of Testing Observations : %d\n", Ot);

		fprintf(fp_console,"\n");
		fprintf(fp_console," Frame Size : %d\n", sizeFrame);	
		fprintf(fp_console," Tokhura Weights : ");
		for(int i=0; i<q; i++){
			fprintf(fp_console,"%0.1f(%d) ", w_tkh[i],i+1);
		}
		fprintf(fp_console,"\n Amplitutde Value to Scale : %d\n", scaleAmp);			
		fprintf(fp_console," Intital Header Lines Ignore Count : %d\n", initIgnoreHeaderLines); 
		fprintf(fp_console," Intital Samples to Ignore : %d\n",initIgnoreSamples);	
		fprintf(fp_console," Intital Noise Frames Count : %d\n",initNoiseFrames);	
		fprintf(fp_console," Noise to Energy Factor : %d\n",thresholdNoiseToEnergyFactor); 
		fprintf(fp_console," Sampling Rate of Recording: %d\n",samplingRate); 

		fprintf(fp_console,"\n =>Total Words in HMM:: %d\n",totWords);
		for(int w=0; w<totWords ;w++)
		{
			fprintf(fp_console," -->W[%d]:[%s]\n",w,HMM_WORDS[w]);
		}
		fprintf(fp_console,"----------------------------------------------------------------\n\n");	

	}
}

void read_words()
{
	FILE *fp_ind;
	char completePathInd[200];
	char word_per_line[num_of_char_per_line];

	sprintf(completePathInd, "%s%s", input_folder,word_file_name);  
	fp_ind = fopen(completePathInd, "r");				
	if(fp_ind == NULL){ 
		perror("\nError: ");
		printf("\nWords File Name is: %s\n", completePathInd);
		getch();
		return;
	}

	totWords=0;
	while(fgets(word_per_line, num_of_char_per_line, fp_ind)!=NULL){
		char* s;
		s=(char*)malloc(sizeof(*s)*(num_of_char_per_line+1)); 
		word_per_line[strlen(word_per_line)-1] = '\0';
		strcpy(s,word_per_line);
		HMM_WORDS[totWords]=s;
		totWords += 1 ;  
	}

	fflush(fp_ind); fclose(fp_ind); 
	
}

void display_words()
{
	printf("\n =>Total Words in HMM:: %d\n",totWords);
	for(int w=0; w<totWords ;w++)
	{
		printf(" -->W[%d]:[%s]\n",w,HMM_WORDS[w]);
	}
}

void add_new_words()
{
	char new_word_name[num_of_char_per_line];
	
	printf("\n Enter New Word To Add (Max Char: %d): ",num_of_char_per_line);
	fgets(new_word_name, num_of_char_per_line, stdin);
	new_word_name[strlen(new_word_name)-1] = '\0';
	printf("\n Word:%s\n",new_word_name);

	for(int w=0; w<totWords ;w++)
	{
		if(_stricmp((HMM_WORDS[w]),(new_word_name))==0)
		{
			 printf("\n Word [%s] Already Exist: Index:W[%d]\n",HMM_WORDS[w] ,w);
			 return;
		}
	}

	FILE *fp_ind;
	char completePathInd[200];

	// create new directory
	int d = totWords; //start from zero, hold total words
	sprintf(completePathInd, "%s%d/", input_folder, d);
	if (!_mkdir(completePathInd))
	{
		 printf("\n Word Directory Created: %s\n",completePathInd);

		 sprintf(completePathInd, "%sTRAINING/%d/", input_live_voice_folder, d);
		 _mkdir(completePathInd);
			printf("\n\t: %s\n",completePathInd);
		 
			sprintf(completePathInd, "%sTESTING/%d/", input_live_voice_folder, d);
		 _mkdir(completePathInd);
			printf("\n\t: %s\n",completePathInd);
		
			sprintf(completePathInd, "%s%d/", filePathInputVoiceTraining, d);
		 _mkdir(completePathInd);
			printf("\n\t: %s\n",completePathInd);
		 
			sprintf(completePathInd, "%s%d/", filePathInputVoiceTesting, d);
		 _mkdir(completePathInd);
			printf("\n\t: %s\n",completePathInd);
		 
			sprintf(completePathInd, "%s%s/%d/", output_folder, output_folder_Model_name, d);
		 _mkdir(completePathInd);
			printf("\n\t: %s\n",completePathInd);

			sprintf(completePathInd, "SONGS/%s", new_word_name);
		 _mkdir(completePathInd);
			printf("\n\t: %s\n",completePathInd);
	}
    else {
        printf("Error:Unable To Create Directory: %s\n", completePathInd);
    }
  
	sprintf(completePathInd, "%s%s", input_folder,word_file_name);  
	fp_ind = fopen(completePathInd, "a");				
	if(fp_ind == NULL){ 
		perror("\nWriting Error: ");
		printf("\nWords File Name is: %s\n", completePathInd);
		getch();
		return;
	}

		char* s;
		s=(char*)malloc(sizeof(*s)*(num_of_char_per_line+1)); 
	strcpy(s,new_word_name);
	HMM_WORDS[totWords]=s;

	fprintf(fp_ind,"%s\n",HMM_WORDS[totWords]);

	fflush(fp_ind); fclose(fp_ind); 
	
	totWords += 1 ;
	display_words();
}

/**************************************************************************************
	Main Function
**************************************************************************************/
int console_main()
{

	 /*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
																		 Intialization
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
	//CalculateWeightsForRaisedSineWindow();	// calculating weights for Raised sine window before hand using in program.
	//read_codebook_from_file();				// read codebook from file.
	//read_words(); 
	// functions are called during form load

	char choice;		// choice exercised.	 
  do{
		int wd; 
		int tot_words_to_use=totWords;
		char ch;
		double accuracy=0, final_accuracy=0;
		unsigned int model_type_use = OutputFolderModel;
		char model_type_string[20] = "new_model";
		bool temp=false;
		char recognised, correct_voice;

		printf("\n\n\n");
		system("pause");
		system("cls");

		printf("\n\n ------- -------~~ HMM MENU ~~------- -------");

		printf("\n d. DISPLAY Common System Settings Used.");
		printf("\n w. DISPLAY Words Used and Index. Total Words:: %d", totWords);

		printf("\n\n 1. OBS SEQ Generation: All Training Files.");
		printf("\n 2. OBS SEQ Generation: All Testing Files.");

		printf("\n\n 3. CONVERGE: Converge Model Lambda for All Words Using Obs Seq Provided. ");

		printf("\n\n 4. TESTING: Offline Testing of All Word: Using Old Input Folder Model");
		printf("\n 5. TESTING: Offline Testing of All Word: Using NEW Converged Output Folder Model");

		printf("\n\n 7. TESTING: Live Testing Any Word: Using Old Input Folder Model.");
		printf("\n 8. TESTING: Live Testing Any Word: Using NEW Converged Output Folder Model.");

		printf("\n\n l. LIVE TRAINING: Single Utterance and Then Train its Model.");

		printf("\n\n r. RECORDING: Recording of WORDS Utterances.");
		printf("\n a. Add NEW Word (Max: %d).", Wmax);
		printf("\n c. CONVERGE: Generate Obs Seq (Training Files) and Converge Model Lambda for Particular NEW Word. ");

		printf("\n\n p. PLAYLIST MENU.");

		printf("\n\n u. CodeBook: Generate Cepstral Coeff Universe File From Training Files.");
		printf("\n\n x. REPLACE: OLD MODEL (Default Input Folder) with NEW CONVERGED MODEL Generated.");

		printf("\n\n n. Exit - Bye		\n\n  --Choice : ");
		scanf("%c%*c", &ch);
		printf("\n <-------->");
        
		switch (ch) {
			case 'd' : DisplayCommonSettings();
				break;
			case 'w' : display_words();
				break;
			case 'a' : display_words();
					   add_new_words();
				printf("\n\n NOTE: Please Make Sure to Add its Utterance in its Index Folder Manually or Use Record Utterance Menu");
				printf("\n\n NOTE: Then Generate Observation Sequence and Converge the Model.");
				printf("\n TRAINING Folder: %s", filePathInputVoiceTraining);
				printf("\n TESTING Folder: %s", filePathInputVoiceTesting);
				break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
											"Training Observation" Sequence Generation for Each Word
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case '1' : 
				// generate observation sequence from the training files. each Word observation sequence is saved in the input lambda folder.
				// also generate normalised files and segrageted data of voice, and analysis of the voice data.
				sequence_generation(TRAINING, On);
				break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
											"Testing Observation" Sequence Generation for Each Word
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case '2' : 
				// generate observation sequence from the testing files. each Word observation sequence is saved in the input lambda folder.
				// also generate normalised files and segrageted data of voice, and analysis of the voice data.
				//sequence_generation(unsigned short int seq_type, int NumOfFiles,  int word_begin=0, int NumOfWords=totWords,  int fileCounter_begin=1)
				
				sequence_generation(TESTING, Ot);
				break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
											Converge Model Lambda For Each Word
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case '3' : 
					for(int d=0; d<totWords; d++){
						/**************** Creating necessary file Path for data. ****************/
						//sprintf(completePathOuput, "%s%s_%d_HMM_Converged_log.txt", output_folder, d);   
						sprintf(completePathOuput, "%s%s_HMM_Converged_log.txt", output_folder, HMM_WORDS[d]);   
						/**************** Opening respective files. ****************/
						fp_console = fopen(completePathOuput, "w");					//to read input observation sequence
						if(fp_console == NULL){ 
								perror("\n Error: ");
								printf("\n File Names is: %s \n ", completePathOuput);
								getch();
								return EXIT_FAILURE;
						}
							fprintf(fp_console, "\n ----------------------- -----------------------> CONVERGING LAMDA : %s <----------------------- -----------------------\n", HMM_WORDS[d]); 	 
							fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 	 
						/**************** Reading  Obs Seq from File ****************/
							readObsSeq(d, TRAINING);		// for each Word read their training sequence observations
							fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 	 

						/**************** Making Converged Lambda From Bakis Model ****************/
							covergence_procedure(On);				// FOR EACH observation seq generate their model and then converge finally by taking average of all.
							output_lambdaABPi_to_each_file(d);
								printf("\n\n\t -------->> New Lambda Files Saved: %s%s/%d/", output_folder, output_folder_Model_name, d);
								printf("\n\n\t -------->> Convergence Done, Log File Generated: %s\n\n", completePathOuput);
									
								fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
								fprintf(fp_console, "\n <---------------------------------- ----------------------------------> END <---------------------------------- -------------------------------------->"); 
						 fflush(fp_console); fclose(fp_console); 
					}// for each Word d<totWords Converge Model Lambda For Each Word
				break;
			case 'c' : 

					printf("\n Enter Particular WORD Index(0-%d): ", totWords-1);
							scanf("%d%*c", &wd);
					sequence_generation(TRAINING, On,wd, wd+1);
						/**************** Creating necessary file Path for data. ****************/ 
						sprintf(completePathOuput, "%s%s_HMM_Converged_log.txt", output_folder, HMM_WORDS[wd]);   
						/**************** Opening respective files. ****************/
						fp_console = fopen(completePathOuput, "w");					//to read input observation sequence
						if(fp_console == NULL){ 
								perror("\n Error: ");
								printf("\n File Names is: %s \n ", completePathOuput);
								getch();
								return EXIT_FAILURE;
						}
							fprintf(fp_console, "\n ----------------------- -----------------------> CONVERGING LAMDA : %s <----------------------- -----------------------\n", HMM_WORDS[wd]); 	 
							fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 	 
						/**************** Reading  Obs Seq from File ****************/
							readObsSeq(wd, TRAINING);		// for each Word read their training sequence observations
							fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 	 

						/**************** Making Converged Lambda From Bakis Model ****************/
							covergence_procedure(On);				// FOR EACH observation seq generate their model and then converge finally by taking average of all.
							output_lambdaABPi_to_each_file(wd);
								printf("\n\n\t -------->> New Lambda Files Saved: %s%s/%d/", output_folder, output_folder_Model_name, wd);
								printf("\n\n\t -------->> Convergence Done, Log File Generated: %s\n\n", completePathOuput);
									
								fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
								fprintf(fp_console, "\n <---------------------------------- ----------------------------------> END <---------------------------------- -------------------------------------->"); 
						 fflush(fp_console); fclose(fp_console); 
					
				break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
											OFFLINE TESTING USING INPUT FOLDER MODEL
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case '4' : 

				model_type_use = InputFolderModel;
				strcpy(model_type_string,"old_model");
				tot_words_to_use=W;

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
											OFFLINE TESTING USING OUTPUT FOLDER MODEL
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case '5' : 
				offline_overall_count=0;
				for(int d=0; d<tot_words_to_use; d++){
					system("cls");
					/**************** Creating necessary file Path for data. ****************/
					//sprintf(completePathOuput, "%s%s_%s_HMM_offline_test_result_%s.txt", output_folder, WordFolderName, WordNames[d],model_type_string);  
					
					sprintf(completePathOuput, "%s%s_HMM_offline_test_result_%s.txt", output_folder, HMM_WORDS[d],model_type_string);
					/**************** Opening respective files. ****************/
					fp_console = fopen(completePathOuput, "w");					//to read input observation sequence
					if(fp_console == NULL){ 
							perror("\n Error: ");
							printf("\n File Names is: %s \n ", completePathOuput);
							getch();
							return EXIT_FAILURE;
					}
						fprintf(fp_console, "\n ----------------------- ----------------------- > OFFLINE TESTING : %s < ----------------------- -----------------------\n",HMM_WORDS[d]); 	 
						fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 	 
					/**************** Reading  Obs Seq from File ****************/
						readObsSeq(d, TESTING);
						fprintf(fp_console, "\n ------------------------------------------------------------------------\n"); 	

					/**************** Offline Testing ****************/
						offline_testing(d, model_type_use);

						 accuracy = (double)(offline_correct_count*1.0/Ot)*100;
						printf("\n\t FOR %s | Accuracy:  %0.2f %%\n\n", HMM_WORDS[d], accuracy); 
							fprintf(fp_console, "\n\t FOR %s | Accuracy:  %0.2f %%\n\n", HMM_WORDS[d], accuracy);

						//printf("\n\n\t -------->> New Lambda Files Saved: %s%s/%d/", output_folder, output_folder_Model_name, d);
						printf("\n\n\t -------->> Offline Testing Done, Log File Generated: %s\n\n", completePathOuput);
							fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
							fprintf(fp_console, "\n <---------------------------------- ----------------------------------> END <---------------------------------- -------------------------------------->"); 
					fflush(fp_console); fclose(fp_console); 
					system("pause");
					
				}// for each Word d<totWords  OFFLINE TESTING
					 final_accuracy = (double)(offline_overall_count*1.0/(Ot*tot_words_to_use))*100;
						printf("\n\t Overall Accuracy:  %0.2f %%\n\n", final_accuracy); 
						
				break;	
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
										Replace OLD MODEL In Default Input Folder with NEW CONVERGED MODEL in Output Folder. 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case 'x' : replace_old_models_files(); 
				break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
										TESTING: Live Testing: Using Old Input Folder Model.
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			
			case '7' : model_type_use = InputFolderModel;
					   strcpy(model_type_string,"old_model");
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
										TESTING: Live Testing: Using New Converged Output Folder Model
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			
			case '8' : 
					printf("\n Duration 3 sec: \n"); 
					timestamp = time(NULL);
					//timestamp = 30;

					/**************** Creating necessary file Path for data. ****************/
					sprintf(liveRecordingFileName, "livetest_%ld", timestamp);  //file_name
					sprintf(liveRecordingCommand, "%s 3 %s %s%s.txt", recording_module_exe_path, liveRecordingWAV, input_live_voice_folder, liveRecordingFileName);  
					//printf("\n path: %s\n",liveRecordingCommand );
					/**************** Creating necessary file Path for data. ****************/
						sprintf(completePathOuput, "%s%s_test_result_%s.txt", input_live_voice_folder, liveRecordingFileName ,model_type_string);  
						/**************** Opening respective files. ****************/
						fp_console = fopen(completePathOuput, "w");					//to read input observation sequence
						if(fp_console == NULL){ 
								perror("\n Error: ");
								printf("\n File Names is: %s \n ", completePathOuput);
								getch();
								return EXIT_FAILURE;
						}
					// Right Click Project Name in Solution Explorer
					// Select Propertes --> Linker --> Input
					// Select Additional Dependencies --> Edit
					// Add winmm.lib
					do{
						
						
						do
						{
							printf("\n Enter To Record.");
							getch();
							printf("\n");
							/**************** Execute the Live Recording Module ****************/
							system(liveRecordingCommand);		//execute the command
							//USAGE : "Recording_Module.exe" <duration_in_seconds> <output_mono_wav_file_path> <output_text_file_path>
						
							printf("\n Playing Sound: "); 
							PlaySound(TEXT(liveRecordingWAV), NULL, SND_SYNC );
							//system(wavform_WAV); // create waveform of file
							printf("\n\n Is Word Correctly Spoken ?" 
								"\n\t	opt = 4: will repeat the recording process. "
								"\n\t	opt = 5: will proceed and do the testing. "
								"\n\n  --Choice :  ");
							//scanf("%c%*c",&correct_voice);
							scanf("%c",&correct_voice);

							while ((getchar()) != '\n');

						}while(correct_voice!='5');
						
						printf("\n\n");

							fprintf(fp_console, "\n ----------------------- ----------------------- > LIVE TESTING : %s < ----------------------- \n",liveRecordingFileName );
						/**************** Live Testing ****************/
							live_testing(model_type_use);

						printf("\n Is Word Correctly Recognised ?" 
								"\n\t	opt = 4: will repeat the recording process. "
								"\n\t	opt = 5: (recognized)will save the file. "
								"\n\t	opt = e: (not recognized) exit this process. "
								"\n\n  --Choice :  ");

						scanf("%c%*c",&recognised);
						fprintf(fp_console, "\n Word Correct Recogntion Status (y=5/n=4/e): %c", recognised); 
						fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
						fflush(fp_console);
					 }while(recognised == '4');
					fprintf(fp_console, "\n ---------------------------------- --------------------------------------"); 
							fprintf(fp_console, "\n <---------------------------------- ----------------------------------> END <---------------------------------- -------------------------------------->"); 
						fflush(fp_console); fclose(fp_console); 
				break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
								Generate Cepstral Coefficients of Training Files
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

			case 'u' :   
					//generate_codebook_universe(TRAINING);
						temp=segregate_speech;
						segregate_speech=false;
						codebook_universe_generation=true;
							sequence_generation(TRAINING,On);
						codebook_universe_generation=false;
						segregate_speech=temp;

				break;

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
								Record Words Menu
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

			case 'r' :   RecordingUtteranceMenu();
				break;

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
							LIVE RECORDING and Training
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case 'l' :   display_words();
						printf("\n Enter Particular Word Index W(0-%d) : ", totWords-1);
						scanf("%d%*c", &wd);
						LiveRecordingTrainingTheOutputModel(wd);
				break;
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
							PLAYLIST MENU
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
			case 'p' :   
						PlayListMenu();
				break;
			case 'n' :   printf("\n Bye \n");  
				break;
			default  :   printf("\n--Invalid Choice. Enter Again \n");
		}//switch
		choice=ch;
	} while (choice != 'n');

	printf("\n---------------------------------- ENTER TO EXIT --------------------------------------\n");
	getch();
	return 0;
}

