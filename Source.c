#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <conio.h>
#include <time.h>
								/*    Functions    */
// Imports all words from file libraries into arrays
void library_importer(void);

//Quote Importer and displayer
void quote_display(void);

// Password Related Functions
char current_password[100] = "default";
void check_password(void);
void change_password(void);

// Password Related End

// Removes common words like 'the' (optimization)
char common_word_remover(char array[]);

// Sad Mood Functions
void sad(void);

//2D Array Sizes for libraries
#define WORDS 200
#define LEN_WORD 100

// Happy Mood Functions and Array Sizes  
#define HELPED 100
#define FRIEND 100
#define MOVIE 100
#define EXERCISE 100
#define SHOP 100
#define SPEECH 100
void happy(void);
void helpedSomeone(void);
void speech(void);
void newFriend(void);
void watchedMovie(void);
void exercise(void);
void Shopping(void);
void unmotivated(void);
void tired(void);
void illness(void);
void alone_bored(void);
/*  If Mood Happy Functions End  */

/*Diary Functions*/
void Write_Diary(void);
void Read_Diary(void);

//Arrays to store words from libraries
char happiness_library[WORDS][LEN_WORD];
char sad_library[WORDS][LEN_WORD];
char illness_library[WORDS][LEN_WORD];
char unmotivated_library[WORDS][LEN_WORD];
char alone_bored_library[WORDS][LEN_WORD];
char tired_library[WORDS][LEN_WORD];
char username[100];

//For Quotes Array and File
#define NO_OF_QUOTES 100
#define QUOTE_LENGTH 1000
char quotes[NO_OF_QUOTES][QUOTE_LENGTH];

int main(void)
{
	library_importer();

	/*Search engine variables start*/
	int i, l, j, k, z;
	int feeling_length, FL, LL = 0, breaker = 0, word_not = 0;
	/*FL is index of first character of each word to be searched in library from feelings.
	Similarly LL is last characters index in feeling array.*/
	char find_word[LEN_WORD], mood_flag = 'F', write_feeling_choice = 'N', ch;
	//Array for input of feelings
	char feeling[1000];
	//Array to place each word from feelings one by one to search into libraries
	char search_word[100];

	
	/*Search engine variables end*/

	printf("\t\t::: Welcome To The Mood Detector and Enhancer! :::\n");
	/*File starts*/
	FILE *datafile;
	char data[1000];
	datafile = fopen("SoftwareFiles/data.txt", "r");
	while (fscanf(datafile, "%s", data) != EOF);
	fclose(datafile);

	FILE *userdetails;
	userdetails = fopen("Userdata/userdetails.txt", "r");
	while (fscanf(userdetails, "%s", username) != EOF);
	fclose(userdetails);
	if (strcmp(data, "Default") == 0)
	{
		printf("Hey dear user!\n\nWhat is your name?\n");
		scanf("%s", username);
		userdetails = fopen("Userdata/userdetails.txt", "w");
		fprintf(userdetails, username);
		fclose(userdetails);
		printf("\n\t%s as you are running this program first time, \n\t", username);
		printf("let us set up a password for this program. \n\tCurrent password is \"default\". \n");
		change_password();
		datafile = fopen("SoftwareFiles/data.txt", "w");
		fprintf(datafile, "Changed");
		fclose(datafile);
	}
	/*File ends*/
	//Calling password function
	check_password();

	do {
		//Resetting variables when mood is not detected and program is used again
		LL = 0, breaker = 0, j = 0, word_not = 0;
		mood_flag = 'F', write_feeling_choice = 'N';

		//Displaces random quote
		quote_display();

		/*search engine starts*/
		printf("\nHey %s! How are you feeling today?\n   >",username);
		//Adding a space at the start of feeling array
		k = 1;
		feeling[0] = ' ';
		//Taking input character by character about mood from user
		while (1)
		{
			ch = getch();
			if (ch == 13)
				break; /*13 is ASCII value of ENTER*/
			if (ch == 8) /*ASCII value of BACKSPACE*/
			{
				putch('\b');
				putch(NULL);
				putch('\b');
				--k;
				continue;
			}

			feeling[k++] = ch;
			putch(ch);
		}
		//Adding a space at the end of feeling array
		feeling[k] = ' ';
		feeling[k + 1] = '\0';
		//Lowering all characters
		strlwr(feeling);
		common_word_remover(feeling);
		feeling_length = strlen(feeling);

		//Finding each word's index in feeling array by detecting spaces
		while (j < feeling_length)
		{
			breaker = 0;
			for (;j < feeling_length;j++)
			{
				if (breaker == 0)
				{
					if (feeling[j] == ' ')
					{
						FL = j + 1;
						breaker++;
						z = j;
					}
				}

				if (j > z)
				{
					if (feeling[j] == ' ')  //Word is detected (because two spaces are detected, between them lies the word)
					{
						LL = j - 1;
						break; //Breaking loop (because mood is detected)
					}
				}

			}

			/*Storing word to be searched in another array*/
			for (l = 0;LL >= FL + l;l++)
			{
				search_word[l] = feeling[FL + l];
			}
			search_word[l] = '\0';
			/*ends*/

			//If not is detected then it will be used later on to do negation of mood
			//for example not with happy makes sad
			if (strcmp("not", search_word) == 0)
			{
				word_not++;
			}

			/*Searching word in all libraries*/
			//If word is found in any library a unique word will be assigned to mood flag indicating mood
			//for example here for sad 'S' is assigned
			for (i = 0; i < 21; i++)
			{
				if (strcmp(sad_library[i], search_word) == 0)
				{
					mood_flag = 'S';
					break;
				}
			}

			for (i = 0; i < 28; i++)
			{
				if (strcmp(unmotivated_library[i], search_word) == 0)
				{
					mood_flag = 'U';
					break;
				}
			}

			for (i = 0; i < 114; i++)
			{
				if (strcmp(happiness_library[i], search_word) == 0)
				{
					mood_flag = 'H';
					break;
				}
			}

			for (i = 0; i < 35; i++)
			{
				if (strcmp(tired_library[i], search_word) == 0)
				{
					mood_flag = 't';
					break;
				}
			}

			for (i = 0; i < 24; i++)
			{
				if (strcmp(alone_bored_library[i], search_word) == 0)
				{
					mood_flag = 'A';
					break;
				}
			}

			for (i = 0; i < 17; i++)
			{
				if (strcmp(illness_library[i], search_word) == 0)
				{
					mood_flag = 'I';
					break;
				}
			}

			//If mood is detected then mood flag will have any of these values else it will have 'F' indicating False
			if (mood_flag == 'T' || mood_flag == 'S' || mood_flag == 'H' || mood_flag == 'U' || mood_flag == 't' || mood_flag == 'A' || mood_flag == 'I')
				break;

		}

		if (mood_flag == 'F')
		{
			printf("\nSorry I could not detect your mood :|\n");
			printf("Wanna write again? (Y/N) : ");
			scanf(" %c", &write_feeling_choice);
		}

		if (mood_flag == 'T' || mood_flag == 'S' || mood_flag == 'H' || mood_flag == 'U')
			break;

	} while (write_feeling_choice != 'N');

	//If he is happy (not is not detected with happiness word or not is detected with sad and similiar negative words)
	if ((mood_flag == 'H' && word_not == 0) || (mood_flag == 'S' && word_not > 0) || (mood_flag == 'I' && word_not > 0) || (mood_flag == 'U' && word_not > 0) || (mood_flag == 't' && word_not > 0))
	{
		happy();
	}

	//If he is happy (not is not detected with sad word or not is detected with happy word)
	else if ((mood_flag == 'S' && word_not == 0) || (mood_flag == 'H' && word_not > 0))
	{
		system("cls");
		printf("\nOh, so %s you are sad. Let me help you to do something to make you happy!\n", username);
		sad();
	}

	else if (mood_flag == 'U')
	{
		unmotivated();
	}

	else if (mood_flag == 't')
	{
		tired();
	}

	else if (mood_flag == 'A')
	{
		alone_bored();
	}

	else if (mood_flag == 'I')
	{
		illness();
	}

	getchar();
	return 0;
}



						/* FUNCTIONS BEGAN */
void check_password()
{
	FILE * password;
	/*password variables*/
	char pw[50], ch;
	int k = 0, j = 0, encryption_var = 0; //encryption var is a variable used is encryption of password
	password = fopen("Userdata/password.txt", "r");
	while (fscanf(password, "%s", current_password) != EOF);
	fclose(password);

	while (1)
	{
		encryption_var = 0;
		if (j == 0)
			puts("\nEnter Password To Proceed: ");
		else
			puts("\nError!\a Enter a valid password : \n");
		k = 0;
		while (1)
		{
			ch = getch();
			if (ch == 13)
				break; //13 is ASCII value of ENTER
			if (ch == 8) //ASCII value of BACKSPACE
			{
				putch('\b');
				putch(NULL);
				putch('\b');
				--k;
				continue;
			}

			pw[k++] = ch;
			ch = '*';
			putch(ch); //Printing * whenever some chacacter is entered
		}
		pw[k] = '\0';

		while (1) //Converting entered password in the form in which encrypted password was saved
		{
			if (pw[encryption_var] == '\0')
				break;
			else
				pw[encryption_var] = pw[encryption_var] + 5;
			encryption_var++;
		}
		if (strcmp(current_password, pw) == 0)
			break;
		j++;
		k = 0;
	}
	system("cls");
}

void change_password(void)
{
	int encryption_var = 0; 
	int i = 0;
	char nothing;
	FILE * f;
	check_password();
	printf("\nEnter new password:\n");
	getchar();
	while (1)
	{
		nothing = getchar();
		if (nothing == '\n')
		{
			current_password[i] = '\0';
			break;
		}
		else
			current_password[i] = nothing;
		i++;
	}
	while (1) //Before saving password encryption of password is done by adding 5 in each character
	{
		if (current_password[encryption_var] == '\0')
			break; //Breaking when whole password is encrypted
		else
			current_password[encryption_var] = current_password[encryption_var] + 5;
		encryption_var++;
	}

	f = fopen("Userdata/password.txt", "w");
	fprintf(f, current_password);
	fclose(f);
	puts("\nPassword updated!");
	puts("Press any key to continue...");
	getch();
	system("cls");
}


void happy(void)
{
	char c;
	int optionWhyAreYouHappy = 0;
	int helped = 0, speechOrBook = 0, friends = 0, achievedGoal = 0, exercised = 0, movie = 0, shopping = 0, withParents = 0;
	/*Storing activities data in file*/
	FILE * activity;
	activity = fopen("SoftwareFiles/count.txt", "a");

	/*-Storing ends-*/
	system("cls");
	printf("\nGreat! %s you seem to me happy today.\n Let me know what you did today ;)",username);
	printf("\n  1. Had a nice meal \n  2. Went out with friends \n  ");
	printf("3. Relaxed \n  4. Reading or listened to some motivational speech\n  ");
	printf("5. Made new friends  \n  6. Achieved your goal  \n  7. Exercised  \n  ");
	printf("8. Watched movie  \n  9. Went for shopping  \n  ");
	printf("10. Spent time with parents, siblings or someone special  ");
	printf("\n  11. Helped someone\n  ");
	printf(" 12. None of these\n");
	printf("\n\n Choose from the given options : ");
	scanf("%d", &optionWhyAreYouHappy);
	if (optionWhyAreYouHappy == 1)
	{
		system("cls");
		fputc('M', activity);
		printf("\n%s thanks for your input! It is added to database.", username);
		printf("\nYou are happy, so am I! Keep eating good stuff!");
		printf("\n You did a great work today. Do you want to share your experience? It will help us to make you happy later on. (Y/N): \n");
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y')
		{
			printf("\nPlease consider some of my questions while writing your experience :-");
			printf("\n-> What did you eat?");
			printf("\n-> Were you alone or you had company?");
			printf("\n-> Did you make it yourself or had it made by someone?");
			Write_Diary();
		}
		else if (c == 'N' || c == 'n')
			printf("\nOkay, not a problem at all! Keep doing great work!\n\n");

	}
	if (optionWhyAreYouHappy == 2)
	{
		system("cls");
		fputc('w', activity);
		printf("\nThanks for your input! It is added to database.");
		printf("\nGood to see that you went out with your friends! Keep your socialisation game strong ;)");
		printf("\n You did a great work today. Do you want to share your experience? It will help us to make you happy later on. (Y/N): \n");
		scanf(" %c", &c);

		if (c == 'Y' || c == 'y')
		{
			printf("\nPlease consider some of my questions while writing your experience :-");
			printf("\n-> Where did you meet them?");
			printf("\n-> Was it pre-planned?");
			printf("\n-> What did you guys do together?");
			Write_Diary();
		}
		else if (c == 'N' || c == 'n')
			printf("\nOkay, not a problem at all! Keep doing great work!\n\n");


	}
	if (optionWhyAreYouHappy == 3)
	{
		system("cls");
		fputc('r', activity);
		printf("\n%s thanks for your input! It is added to database.", username);
		printf("\n I am happy for you. It is good to have some rest ocassionally. It is all about finding calm in the chaos.\n");
		printf("\n You did a great work today. Do you want to share your experience? It will help us to make you happy later on. (Y/N): \n");
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y')
		{
			Write_Diary();
		}
		else if (c == 'N' || c == 'n')
			printf("\nOkay, not a problem at all! Keep doing great work!\n\n");


	}
	if (optionWhyAreYouHappy == 4)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('s', activity);
		speech();
	}
	if (optionWhyAreYouHappy == 5)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('f', activity);
		newFriend();
	}
	if (optionWhyAreYouHappy == 6)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('g', activity);
		printf("Brilliant. Keep up the good work! Success gives us pleasure and happiness");
	    printf("but don't forget that you still have a long way to go. Celebrate success and move on to your next goal!");
		printf("\n You did a great work today. Do you want to share your experience? It will help us to make you happy later on. (Y/N): \n");
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y')
			Write_Diary();
		else if (c == 'N' || c == 'n')
			printf("\nOkay, not a problem at all! Keep doing great work!\n\n");

	}
	if (optionWhyAreYouHappy == 7)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('e', activity);
		exercise();
	}
	if (optionWhyAreYouHappy == 8)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('m', activity);
		watchedMovie();
	}
	if (optionWhyAreYouHappy == 9)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('S', activity);
		printf("Cool.. You went for shopping.\nShopping makes everyone happy!\n");
		printf("I think if shopping doesn't make you happy then you are in the wrong shop.");
	    Shopping();
	}
	if (optionWhyAreYouHappy == 10)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('p', activity);
		printf("Good to see that you spent time with your family.\n Many of us spend their time on what is urgent not on what is important.\n");
		printf("\n You did a great work today. Do you want to share your experience? It will help us to make you happy later on. (Y/N): \n");
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y')
			Write_Diary();
		else if (c == 'N' || c == 'n')
			printf("\nOkay, not a problem at all! Keep doing great work!\n\n");

	}
	if (optionWhyAreYouHappy == 11)
	{
		system("cls");
		printf("\n%s thanks for your input! It is added to database.\n", username);
		fputc('h', activity);
		helpedSomeone();
	}
	fclose(activity);

	if (optionWhyAreYouHappy == 12)
	{
		system("cls");
		printf("\nOh, I see. You were not able to find what you did in given options. Why don't you write that?\n", username);
		printf("So, do you want to share your experience? It will help us to make you happy later on. (Y/N): \n");
		scanf(" %c", &c);
		if (c == 'Y' || c == 'y')
			Write_Diary();
		else if (c == 'N' || c == 'n')
			printf("\nOkay, not a problem at all! Keep doing great work!\n\n");

	}
}


void helpedSomeone()
{
	char nothing;
	char howYouHelped[HELPED];
	char option = 'x';
	printf("\n You did a great work today. Do you want to share your experience? It will help us to make you happy later on. (Y/N): \n");
	scanf(" %c", &option);
	if (option == 'Y' || option == 'y')
	{
		printf("\nPlease consider some of my questions while writing your experience :-");
		printf("\n-> How did you help the person?");
		printf("\n-> Why did you help the person?");
		printf("\n-> How did he react after being helped by you?");
		Write_Diary();
	}

	else if (option == 'n' || option == 'N')
	{
		printf("\nOkay, not a problem at all! Keep doing great work!\n\n");
	}

}

void speech()
{
	char option = 'x';
	printf("\n Wow! you did a great work today. Do you want to share your experience? It will be a great pleasure for us.(Y/N) ");
	scanf(" %c", &option);
	if (option == 'Y' || option == 'y')
	{
		printf("\nPlease consider some of my questions while writing your experience :-");
		printf("\n-> Why did you listen to this talk? ");
		printf("\n-> Was it inspiring? ");
		printf("\n-> Who is your favorite speaker? ");
		Write_Diary();
		//break;
	}
	else if (option == 'n' || option == 'N')
	{
		printf("\nOkay No problem. As you wish. :)\n\n");
	}
}

void newFriend()
{

	char option = 'x';
	printf("\n Wow! Do you want to share your experience? It will be a great pleasure for us.(Y/N) ");
	scanf(" %c", &option);
	if (option == 'Y' || option == 'y')
	{
		printf("\nPlease consider some of my questions while writing your experience :-");
		printf("\n-> What's your friend's name?");
		printf("\n-> What was his/her first impression when you saw him/her?");
		printf("\n-> What's his/her hobby?");
		Write_Diary();
	}
	else if (option == 'n' || option == 'N')
	{
		printf("\nOkay No problem. As you wish. :)\n\n");
	}
}

void exercise()
{
	char option = 'x';
	printf("\n WoW! you did a great work today. Do you want to share your experience? It will be a great pleasure for us.(Y/N) ");
	scanf(" %c", &option);
	if (option == 'Y' || option == 'y')
	{
		printf("\nPlease consider some of my questions while writing your experience :-");
		printf("\n-> Okay! How was the exercise?");
		printf("\n-> Was it tiring?");
		printf("\n-> Are you feeling in a bit of shape now?");
		Write_Diary();
	}
	else if (option == 'n' || option == 'N')
	{
		printf("\nOkay no problem. As you wish but please continue exercising. :)\n\n");
	}
}

void watchedMovie()
{
	char bestMovie[MOVIE];
	char dislikeMovieType[MOVIE];
	char whyDislikeMovie[MOVIE];
	char fictionNon[MOVIE];
	char optionDislikeMovieOrNot = 'x';
	char option = 'x';
	printf("\n Ahan.. So you went to watch a movie today. Do you want to share your experience with us? (Y/N) ");
	scanf(" %c", &option);
	if (option == 'Y' || option == 'y')
	{
		printf("\nPlease consider some of my questions while writing your experience :-");
		printf("\n -> What was the movie about?");
		printf("\n -> Was it an interesting movie?");
		printf("\n -> What kind of movies do you like?");
		
	}
	else if (option == 'n' || option == 'N')
	{
		printf("\nOkay No problem.\n\n");
	}
}

void Shopping(void)
{
	char type[SHOP];
	// char gooodOrNot[SHOP];
	char c = 'x';
	printf("\n Great!\nYou know what teling someone about your happy moments helps you to remember them forever.");
	printf("\nWould  you like to share your experience ? (Y\N)");
	scanf(" %c", &c);
	if (c == 'Y' || c == 'y')
		Write_Diary();
	else if (c == 'n' || c == 'N')
		printf("\nOkay No problem. As you wish. :)\n\n");

}


void unmotivated(void)
{	
	char c = 'x';
	printf("\nOh.. You seem so unmotivated. Life is full of ups and downs. \nYou have to face reality of life.\n Let me help you a bit in overcoming this situation");
	printf("\n1. Share your problem With someone.\n2. Listen to some motivational speeches.\n3. Don't lose hope and prepare yourself to overcome the situations like this.\n");
	printf("4. Make a list of your priorities\n5. Have a good cry.\n6. Wear clothes that make you feel good.\n");
	printf("7. Think about your goals and what can you do to achieve them. \nOfcourse losing hope is not a choice\n");
	printf("8. Give yourself appreciation for all the good things you have done till now.\n9. Replace the negative thoughts in your mind with the positive ones\n");
	printf("10. Celebrate the small achievements.");
	printf("Here is a quote to motivate you:\n \"You cannot always control what goes on outside but you can always control what goes on inside.\" ");

	printf("\n\nDo you want to me to display your diary?\nIt may make you feel better.(Y/N):\n");
	scanf(" %c", &c);
	if (c == 'Y' || c == 'y')
		Read_Diary();
	else if (c == 'N' || c == 'n')
		printf("\nOkay, not a problem at all!\n\n");
}

void illness(void)
{
	char c = 'x';
	printf("\nOh I see you are not feeling well. ");
	printf("\nI think you should have some rest\nIf that doesn't help then you should take some medicine like paracetamol.\n");
	printf("If anyone of these is not working then it is time to visit doctor!\n");
	printf("\n\nDo you want to me to display your diary?\nIt may make you feel better.(Y/N):\n");
	scanf(" %c", &c);
	if (c == 'Y' || c == 'y')
		Read_Diary();
	else if (c == 'N' || c == 'n')
		printf("\nOkay, not a problem at all!\n\n");

}

void tired(void)
{
	char c = 'x';
	int option;
	printf("\nOh, so you are tired. \nLet me know what is the reason of your tiredness!");
	printf("\nIs it because of : \n  1. BOSS\n 2. OFFICE WORK\n 3. HOUSEHOLD WORK\n 4. LONG TRAVELLING\n 5. DAIL ROUTINE\n 6. SOME OTHER REASONS\n");
	scanf("%d", &option);
	if (option == 2 || option == 3 || option == 6)
	{
		printf("Let me suggest some ways to relieve your pain\n");
		printf("1.Take a nap.\n 2.Take a hot Shower.\n 3.Have a massage\n 4.Take a break from the work.\n");
	}
	if (option == 4 || option == 5)
	{
		printf("Let me suggest some ways to relieve your pain\n");
		printf("1.Take a nap.\n 2.Take a hot Shower.\n 3.Have a massage\n 4.Take a break from the work.\n");
	}
	if (option == 1)
	{
		printf("Boss is always a troublesome person. Try to find a job you love and love what you do to keep away your tiredness.");
	}
	printf("\n\nDo you want to me to display your diary?\nIt may make you feel better.(Y/N):\n");
	scanf(" %c", &c);
	if (c == 'Y' || c == 'y')
		Read_Diary();
	else if (c == 'N' || c == 'n')
		printf("\nOkay, not a problem at all!\n\n");

}

void alone_bored(void)
{
	char c = 'x';
	{
		int	optionWhyAreYouBored;
		printf("\nWell, you seem to me bored. No worries I am here \nto rescue you! Just think about below given options what do you want to do? ");
		printf("\n  1. Activity suggestion");
		printf("\n  2. Nurture yourself \n  3. Be creative \n  ");
		printf("4. Engage your brain \n  5. Relax \n  6. Be social \n  ");
		printf("  Choose from the given options: ");
		scanf("%d", &optionWhyAreYouBored);

		if (optionWhyAreYouBored == 1)
		{
			system("cls");
			printf("\n1. Watch something funny.\n2. hangout with your friends.\n");
			printf("3. Talk to someone close to you.\n4. Do something silly that you will enjoy.\n");
			printf("5. Go for a walk.\n6. Do something new.\n7. Cook a new recepie.\n");
			printf("8. Go to coffee with someone new.\n9. vlolunteer for the cause that means something to you.\n");
			printf("10. Sing for yourself.\n11. Remove toxic relationships from your life.\n");
			printf("12. Give yourself some quality time.\n13. Make a fort in your living room.\n");
			printf("14. Redecorate your room.\n15. Indulge in reading a book for few hours.\n ");
		}

		if (optionWhyAreYouBored == 2)
		{
			system("cls");
			printf("\nSo you want to nurture yourself. Good.... Let's try any of these:\n");
			printf(" . Drink a cup of hot tea.\n");
			printf(" . Listen to the music.\n");
			printf(" . Get a haircut!\n");
			printf(" . Take a bath.\n");
			printf(" . Blow bubbles.\n");
		}
		if (optionWhyAreYouBored == 3)
		{
			system("cls");
			printf("\nSo you want to do something creative. Good.... Let's try any of these:\n");
			printf(" . Invent something random.\n");
			printf(" . Doodle.\n");
			printf(" . Decorate your house.\n");
			printf(" . Paint something. Play with colors\n");
			printf(" . Take photographs.\n");
		}
		if (optionWhyAreYouBored == 4)
		{
			system("cls");
			printf("\nSo you want to engage your brain. Good.... Let's try any of these:\n");
			printf(" . Do a crossword puzzle.\n");
			printf(" . Research some new technology.\n");
			printf(" . Visit library.\n");
			printf(" . Write an article.\n");
			printf(" . Complete a maze.\n");
		}
		if (optionWhyAreYouBored == 5)
		{
			system("cls");
			printf("\nSo you want to relax. Good.... Let's try any of these:\n");
			printf("You can watch some funny serials and movies like:\n . FRIENDS\n . HOW I MET YOUR MOTHER\n . SCOBBY DOO.\n . SHAOLIN SOCCOR.\n . KUNG FU PANDA\n");
		}
		if (optionWhyAreYouBored == 6)
		{
			system("cls");
			printf("\nSo you want to socialize. Good.... Let's try this:\n");
			printf(" . Make a gift for someone.\n");
			printf(" . Give some money away.\n");
			printf(" . Visit library.\n");
			printf(" . Go for shopping.\n");
			printf(" . Call to some random friend.\n");
			system("pause");
		}
		printf("\n\nDo you want to me to display your diary?\nIt may make you feel better.(Y/N):\n");
		c = getch();
		if (c == 'Y' || c == 'y')
			Read_Diary();
		else if (c == 'N' || c == 'n')
			printf("\nOkay, not a problem at all!\n\n");

	}
}

/*This fucntion actually scans characters from a file, each character indicates
  an activity which user did in the past and that made him happy. It counts how 
  many times he did that activity in the past and shows that to user to suggest him.*/

void sad(void)
{
	FILE *activityc;
	char ch = 'x', c = 'x';
	int helped = 0, speech = 0, movies=0, newfriend = 0, goal = 0, exercise = 0, parents = 0, meal = 0, hangout = 0, shopping = 0, relaxed=0;
	activityc = fopen("SoftwareFiles/count.txt", "r"); 
	while (1)        
	{
		ch = fgetc(activityc);
		if (ch == EOF)
			break;
		if (ch == 'h')
			helped++;
		if (ch == 's')
			speech++;
		if (ch == 'f')
			newfriend++;
		if(ch == 'g')
			goal++;
		if (ch == 'e')
			exercise++;
		if (ch == 'p')
			parents++;
		if (ch == 'S')
			shopping++;
		if (ch == 'r')
			relaxed++;
		if (ch == 'w')
			hangout++;
		if (ch == 'M')
			meal++;
		if (ch == 'm')
			movies++;
		
	}
	printf("Let us look at the things you did in the past to make yourself happy.\n");
			printf("\n\t1. You helped someone '%d' times which made you happy.\n\n",helped);
			printf("\t2. You read books and heard to some motivational speech '%d' times.\n\n",speech);
			printf("\t3. You made a new friend '%d' times.\n\n",newfriend);
			printf("\t4. You achieved your goal '%d' times, no matter short term or long term, and that was helpful in the past.\n",goal);
			printf("\tWhy don't you start working on some of your goals?\n\n");
			printf("\t5. You exercised '%d' times.\n\n",exercise);
			printf("\t6. You spent time with your parents and siblings '%d' times.\n\n",parents);
			printf("\t7. You had a nice meal '%d' times which made you happy! Why don't you go and eat something delicious again?\n\n", meal);
			printf("\t8. You went out with your friends '%d' times which made you happy in the past. Let's just call some friend ;)\n\n", hangout);
			printf("\t9. You took time for rest '%d' times and that made you happy. Why don't you take a nap?\n\n", relaxed);
			printf("\t10. You went for shopping '%d' times and I remember that too made you happy.\n\n", shopping);
			printf("\t11. You watched movies '%d' times in the past and that day you really seemed to me happy.\n\n", movies);
	fclose(activityc);

	printf("\n\nDo you want to me to display your diary?\nIt may make you feel better.(Y/N):\n");
	scanf(" %c", &c);
	if (c == 'Y' || c == 'y')
		Read_Diary();
	else if (c == 'N' || c == 'n')
		printf("\nOkay, not a problem at all!\n\n");

}


/*This function removes common words if it is used again and again, for now it only removes 'the'. 
  This allows us to save time while searching a word in libraries containing 1000+ words.
  */
char common_word_remover(char array[])
{
	int i;
	char * temporaryfeelingarray = (char *)malloc(array);
	strcpy(temporaryfeelingarray, array);
	char * s = temporaryfeelingarray; /*Base address of the string*/
	char * p = array; /*Base address of new string*/
	char *q;
	while (*s)
	{
		q = s;
		if (*s == 't')
		{
			s++;
			if (*s == 'h')
			{
				s++;
				if (*s == 'e')
				{
					s++;
					if (*s == ' ')
						;
					else
					{
						for (i = 0; i <= 3;i++)
							*p++ = *q++;
					}
				}
			}
			else
			{
				*p++ = *q++;
				s--;
			}
		}
		else
			*p++ = *s;
		s++;
	}
	*p = '\0';
	return (array);
}

/*This function imports all the words from the library files and puts them in a 2D array
  which is later used to search words for mood detection*/
void library_importer(void)
{
	int i = 0, j = 0, no_of_words = 0;
	char temp_for_transfer[LEN_WORD]; //Stores single line from file temporarily
	/*importing from happy library*/
	FILE * fp;
	fp = fopen("Libraries/happiness_library_file.txt", "r"); //Opening file from which words are to be imported
	if (fp == NULL)
	{
		puts("File not found!");
		exit(0);
	}
	while (fgets(temp_for_transfer, 49, fp) != NULL) //This places each line from file in a slot of 2D array
	{
		for (j = 0;j<LEN_WORD;j++)
		{
			if (temp_for_transfer[j] == '\n') //Whenever '\n' is detected that means one line ends
			{
				happiness_library[i][j] = '\0'; //So '\0' is placed at the end of slot and loop is stopped
				break;
			}
			happiness_library[i][j] = temp_for_transfer[j]; //Now each line is transfer into 2D array from temporary 1D array which stored a single line from file
		}
		i++;
		no_of_words++;
	}
	fclose(fp);

	/*Importing from sad library*/
	FILE *fp2;
	i = 0, j = 0, no_of_words = 0;
	fp2 = fopen("Libraries/sad_library_file.txt", "r"); //Same criteria is followed as above
	if (fp2 == NULL)
	{
		puts("File not found!");
		exit(0);
	}
	while (fgets(temp_for_transfer, 49, fp2) != NULL)
	{
		for (j = 0;j<LEN_WORD;j++)
		{
			if (temp_for_transfer[j] == '\n')
			{
				sad_library[i][j] = '\0';
				break;
			}
			sad_library[i][j] = temp_for_transfer[j];
		}
		i++;
		no_of_words++;
	}
	fclose(fp2);

	/*importing from unmotivated library*/
	FILE *fp3;
	i = 0, j = 0, no_of_words = 0;
	fp3 = fopen("Libraries/unmotivated_library_file.txt", "r");
	if (fp3 == NULL)
	{
		puts("File not found!");
		exit(0);
	}
	while (fgets(temp_for_transfer, 49, fp3) != NULL)
	{
		for (j = 0;j<LEN_WORD;j++)
		{
			if (temp_for_transfer[j] == '\n')
			{
				unmotivated_library[i][j] = '\0';
				break;
			}
			unmotivated_library[i][j] = temp_for_transfer[j];
		}
		i++;
		no_of_words++;
	}
	fclose(fp3);

	/*importing from illness library*/
	FILE *fp4;
	i = 0, j = 0, no_of_words = 0;
	fp4 = fopen("Libraries/illness_library_file.txt", "r");
	if (fp4 == NULL)
	{
		puts("File not found!");
		exit(0);
	}
	while (fgets(temp_for_transfer, 49, fp4) != NULL)
	{
		for (j = 0;j<LEN_WORD;j++)
		{
			if (temp_for_transfer[j] == '\n')
			{
				illness_library[i][j] = '\0';
				break;
			}
			illness_library[i][j] = temp_for_transfer[j];
		}
		i++;
		no_of_words++;
	}
	fclose(fp4);

	/*Importing from Alone-Bored library*/
	FILE *fp5;
	i = 0, j = 0, no_of_words = 0;
	fp5 = fopen("Libraries/alone_bored_library_file.txt", "r");
	if (fp5 == NULL)
	{
		puts("File not found!");
		exit(0);
	}
	while (fgets(temp_for_transfer, 49, fp5) != NULL)
	{
		for (j = 0;j<LEN_WORD;j++)
		{
			if (temp_for_transfer[j] == '\n')
			{
				alone_bored_library[i][j] = '\0';
				break;
			}
			alone_bored_library[i][j] = temp_for_transfer[j];
		}
		i++;
		no_of_words++;
	}
	fclose(fp5);

	/*Importing from Tired library*/
	FILE *fp6;
	i = 0, j = 0, no_of_words = 0;
	fp6 = fopen("Libraries/tired_library_file.txt", "r");
	if (fp6 == NULL)
	{
		puts("File not found!");
		exit(0);
	}
	while (fgets(temp_for_transfer, 49, fp6) != NULL)
	{
		for (j = 0;j<LEN_WORD;j++)
		{
			if (temp_for_transfer[j] == '\n')
			{

				tired_library[i][j] = '\0';
				break;
			}
			tired_library[i][j] = temp_for_transfer[j];
		}
		i++;
		no_of_words++;
	}
	fclose(fp6);
}

/*This function imports all the quotes from file and  displaces a quote on screen. 
  Purpose of putting this in an array is to use it again and again.*/
void quote_display(void)
{
	system("cls");
	srand(time(NULL));
	int i = 0, j = 0, no_of_words = 0;
	char temp_for_transfer[QUOTE_LENGTH];

	FILE * fp7;
	fp7 = fopen("Libraries/Frontend/Quotes.txt", "r");
	if (fp7 == NULL)
	{
		puts("Quotations file not found!");
		exit(0);
	}
	while (fgets(temp_for_transfer, QUOTE_LENGTH, fp7) != NULL)
	{
		for (j = 0;j<QUOTE_LENGTH;j++)
		{
			if (temp_for_transfer[j] == '\n')
			{

				quotes[i][j] = '\0';
				break;
			}
			quotes[i][j] = temp_for_transfer[j];
		}
		i++;
		no_of_words++;
	}
	fclose(fp7);

	do
	{
		i = rand() % 100;
	} while (i < 0 && i > NO_OF_QUOTES);
	printf("Quick Quote:\n\n\t");
	for (j = 0;j < QUOTE_LENGTH;j++)
	{
		if (quotes[i][j] == '\0')
			break;
		printf("%c",quotes[i][j]);
	}
	printf("\n\n\n\t:: Press enter key to continue  ::");
	getchar();
	system("cls");
}

/* This function enables user to write diary when he is happy and store it in a file*/
void Write_Diary()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%B-%Y.", timeinfo);
	printf("\n\n");
	puts(buffer);

	FILE *fp;
	char ch = ' ';

	fp = fopen("Userdata/Diary.txt", "a");

	fputs("\n\n", fp);
	strcat(buffer, " :- ");
	fputs(buffer, fp);

	printf("\n\nPlease write about your day and press (CTRL+Z) in the next line when you are finished: \n\n");
	while ((ch = getchar()) != EOF)
		putc(ch, fp);

	fclose(fp);
}

/*This function displaces diary when user is not happy*/
void Read_Diary()
{
	FILE *fp;
	char ch = ' ';
	printf("\n\n\t\t\t\t:: DIARY ::\n\n");
	fp = fopen("Userdata/Diary.txt", "r");
	while ((ch = getc(fp)) != EOF)
		printf("%c", ch);
	fclose(fp);
	printf("\n\n\t\t\t\t:: DIARY ENDS ::\n");
	getchar();
}

