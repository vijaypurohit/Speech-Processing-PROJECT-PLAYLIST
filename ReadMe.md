>Speech Processing CS 566
>
>**PROJECT (SPEECH BASED PLAYLIST)**
>
>Roll No: 214101058 MTech CSE'23 IITG | Vijay Purohit

----------------------------------------------------
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

----------------------------------------------------
##### FILES:
   * main_hmm.cpp	= Main File Contains Menu for interactive session
   * hmm_testing.h	= Contains HMM offline and live testing functions
   * observation_sequence.h	= Contains Observation Sequence Generation Functions, calculating coefficients, marker etc for preprocesing of speech.
   * hmm_solutions.h	= contains functions for solutions of problem one two and three for HMM.
   * hmm_record.h	= contains functions for recording the utterances.
   * hmm_playlist.h	= playlist menu and contains functions for showing playlist and playing songs.
   * WndMainPlayList.h	= Microsoft Form for GUI of Playlist. Contains functions for GUI handling

##### For Error: PlaySound() is not Identified: Do:
   * Right Click Project Name in Solution Explorer
   * Select Propertes --> Linker --> Input
   * Select Additional Dependencies --> Edit
   * Add name " winmm.lib "
----------------------------------------------------
### Instructions to execute Code.
1. Open it in Visual Studio 2010.
2. Compile it and Run. GUI window will be shown along with console.
   * Interact With Menu
      * Output will be shown on the Console.
      * Detailed Output *.txt will be present in their respective folder.
3. Take Care:
   * To generate The Respective Sequence (Training/Testing) before Converging or Testing.	
4. Please Add 5 Songs of the playlist in the respective folder within SONGS.

----------------------------------------------------
### DOC FOLDER 
   * [REPORT](../origin/DOC/SP_CS566_Project_PLAYLIST_REPORT.pdf)
   * [FLOWCHART](../origin/DOC/flowchart.jpg)
   * VIDEO LINK<a href="http://www.youtube.com/watch?feature=player_embedded&v=cLdlCeDYFj8" target="_blank"> <img src="http://img.youtube.com/vi/cLdlCeDYFj8/0.jpg"  alt="Playlist Demo" width="240" height="180" border="10"/></a>
----------------------------------------------------
THE END.
