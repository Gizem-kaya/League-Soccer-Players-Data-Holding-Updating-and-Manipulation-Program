struct footballer {				/* For each footballer there is a struct.*/
    char f_name[100];
    char team_name[100];
    struct match * next_match;
    struct footballer * next_footballer;
};

struct match {					/* For each match of given footballer there is a struct.*/
	struct match * prev;
    char away_team[100];
    int min_of_goal;
    int match_id;
    struct match * next;
};

struct goal_score {				/* Holds given footballer's name, team and score count.*/
	char scorer_name[100];
	char scorer_team[100];
	int score_count;
};

#include <bits/stdc++.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <stdio.h> 
#include <algorithm>
#include <cmath>
#include <cstdio>


using namespace std;

namespace {
    struct first_word {																/* A function for sorting the lines.*/
        bool operator()(const string& a, const string& b)
        {																			/* Firstly, sorts by names. If two names are same it sorts by the match id value.*/
        	
        																			/* Finally, If match ids are also same, then it sorts by minute of goal values.*/
        	char name1[200];
        	strcpy(name1,a.substr(0, a.find_first_of(",")).c_str());
        	char name2[200];
        	strcpy(name2,b.substr(0, b.find_first_of(",")).c_str());
        
        	int id1;
        	int id2;

        	sscanf(a.substr(a.find_last_of(",")+1).c_str(), "%d", &id1);
        	sscanf(b.substr(b.find_last_of(",")+1).c_str(), "%d", &id2);
        	
        	int min1;
        	int min2;
        	char temp1[200];
        	char temp2[200];
        	char temp11[200];
        	char temp22[200];


        	strcpy(temp11,((a.substr(0,a.find_last_of(","))).substr((a.substr(0,a.find_last_of(","))).find_last_of(",")+1)).c_str());
        	strcpy(temp22,((b.substr(0,b.find_last_of(","))).substr((b.substr(0,b.find_last_of(","))).find_last_of(",")+1)).c_str());
       		sscanf(temp11, "%d", &min1);
       		sscanf(temp22, "%d", &min2);
       
        	if(!strcmp(name1 ,name2) ){
        		if(id1 == id2){
        			if(min1 == min2){
        				return 1;
					}
					else if(min2 > min1){
						return 1;
					}
					else{
							return 0;
					}
        		
				}
				else if(id1 < id2){
					return 1;
				}
				else{
					return 0;
				}
        		
			}
			else if(strcmp(name1,name2)>0){
				
				return 0;
				
			}
			else{
				return 1;
			}
            
        }
    };
}



void split(const string& s, char c, vector<string>& v) {		/* The function for splitting the strings by ','.*/
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

void append_to_list(struct footballer** head_ref_footballer, char* new_f_name, char* new_team_name, char* new_away_team, int new_min_of_goal, int new_match_id, int cont)    /* For adding an element to footballers linked list or matches doubly linked list.*/
{ 
   if(cont == 0){					/* If the footballer is coming for the first time.*/
  
    footballer* new_footballer = new footballer();   			/* Creates a new footballer.*/
   	match* new_match = new match ();    				/* Creates a new match for the new footballer.*/
  
    struct footballer* last_footballer = *head_ref_footballer; 		

   	strcpy(new_footballer->f_name , new_f_name);
   
	strcpy(new_footballer->team_name , new_team_name);
	strcpy(new_match->away_team , new_away_team); 

	new_match->min_of_goal = new_min_of_goal;
	new_match->match_id = new_match_id; 
 
   
    new_footballer->next_footballer = NULL; 
     

    while (last_footballer->next_footballer != NULL){			/* For finding the last footballer of the linked list.*/
        last_footballer = last_footballer->next_footballer; 
  	}
	
    last_footballer->next_footballer = new_footballer; 

	new_footballer->next_match = new_match;
	new_match->next= NULL;
	new_match->prev= NULL;


	}

	else if (cont == 1){ 					/* If the footballer already exists, then add the match values.*/
	
	struct match* new_match = new match();
	
	struct footballer* dumb_head_footballer = (*head_ref_footballer); 


	while(string(dumb_head_footballer->f_name) != string(new_f_name)){	/* For finding the given footballer on the linked list.*/
		
		dumb_head_footballer = dumb_head_footballer->next_footballer;
		
	}

	struct match* last_match = dumb_head_footballer->next_match;
	
	while(last_match->next != NULL){		/* For finding the last match of the given footballer.*/
		last_match = last_match->next;
	}

	last_match->next = new_match;
	new_match->prev = last_match;
	new_match->next = NULL;
	strcpy(new_match->away_team , new_away_team);
    new_match->min_of_goal = new_min_of_goal;
    new_match->match_id = new_match_id;
	

	}

} 


void create_head(struct footballer** head_ref_footballer, char* new_f_name, char* new_team_name, char* new_away_team, int new_min_of_goal, int new_match_id) {	/* Just for the first footballer creation.*/
	
   	footballer* new_footballer = new footballer(); 		
   	match* new_match = new match ();					/* First footballer's first match.*/
   	
   	strcpy(new_footballer->f_name , new_f_name); 
	strcpy(new_footballer->team_name , new_team_name);
	strcpy(new_match->away_team , new_away_team); 
	new_match->min_of_goal = new_min_of_goal;
	new_match->match_id = new_match_id;

  	new_footballer->next_footballer = NULL; 
  	new_footballer->next_match = new_match; 

    (*head_ref_footballer) = new_footballer; 
    
    new_match->prev = NULL;
	new_match->next = NULL;
 	
}




void matches_of_footballers(ofstream &output, struct footballer** head_ref_footballer, char input[]){	/* Searchs for the given footballer's match informations.*/
	
	struct footballer* temp_pointer_footballer = *head_ref_footballer; 

	for( ; temp_pointer_footballer ; temp_pointer_footballer = temp_pointer_footballer->next_footballer){	/* Iterate over the footbalers.*/
		if (string(temp_pointer_footballer->f_name) == string(input)){		/* Given footballer's name is found.*/
			
			output << "Matches of "<< temp_pointer_footballer->f_name <<'\n';
			
			struct match* temp_pointer_match = temp_pointer_footballer->next_match; 
			
			for( ; temp_pointer_match ; temp_pointer_match = temp_pointer_match->next){	/* Iterate over the given footballer's matches.*/
		
					output << "Footballer Name: "<<temp_pointer_footballer->f_name<<",Away Team: "<<temp_pointer_match->away_team<<",Min of Goal: "<<temp_pointer_match->min_of_goal<<",Match ID: "<<temp_pointer_match->match_id<<'\n';
			}
			temp_pointer_match = temp_pointer_footballer->next_match;
		}
	}
	

	free(temp_pointer_footballer);

}


void team_list(ofstream &output, struct footballer** head_ref_footballer){	/* For printing the whole team list.*/
	
	struct footballer* temp_pointer_footballer = *head_ref_footballer; 
	
	vector<string> team_array;			/* An array for teams.*/
	
	for( ; temp_pointer_footballer ; temp_pointer_footballer = temp_pointer_footballer->next_footballer){
	
	
		if ( std::find(team_array.begin(), team_array.end(), string(temp_pointer_footballer->team_name)) != team_array.end() ){		/* If the current team name is already in the team_array vector.*/
				/* Don't push the current team name to the team_array vector.*/
		}
		else{
			team_array.push_back (temp_pointer_footballer->team_name);	/* If the current team name is coming for the first time.*/
		}																	/* Add the current team name to the team_array vector.*/
		
	}
	
	for(int i=0; i<team_array.size(); ++i)			/* Print the team_array vector's elements.*/
  		output << team_array[i] << '\n';
}



int order_match(ofstream &output, struct footballer** head_ref_footballer, char input[], int parameter){	/* Prints the given footballer's matches in ascending order or descending order.*/
	
	struct footballer* temp_pointer_footballer = *head_ref_footballer; 

		
	for( ; temp_pointer_footballer ; temp_pointer_footballer = temp_pointer_footballer->next_footballer){	/* Iterate over the footbalers.*/
	
		struct match* temp_pointer_match = temp_pointer_footballer->next_match; 

		if (string(temp_pointer_footballer->f_name) == string(input) || parameter == 2){					/* Given footballer's name is found or the function calls for Hat-Trick command.*/
		
		
			int match_id_array[100];
			int i = 0;
			int k; 
			int c = 0;
			int goal_count = 1;
			
			for( ; temp_pointer_match ; temp_pointer_match = temp_pointer_match->next){	 /* Iterate over footballers' matches.*/
			
				
				
				for(k = 0;k<i;k++){
				
					if(temp_pointer_match->match_id == match_id_array[k]){		/* If the current match id comes before.*/
 						 c = 1;
						 goal_count++;								
						 break;
						 
					}
					else{
						c = 0;
					}
									
					
				}
				if(temp_pointer_match && c == 0){
				
					match_id_array[i]= temp_pointer_match->match_id;
				
					i++;
				}
						
							
			}	
			if (parameter == 0){				/* For ascending order.*/
				std::sort(match_id_array, match_id_array+(i));
			}
			else if(parameter == 1){															/* For descending order.*/
				std::sort(match_id_array, match_id_array+(i), greater<int>());
			}
			if (parameter != 2){			/* For ascending order or descending order.*/
			
				for(int t = 0; t<i; t++){
					output << "footballer Name: "<<temp_pointer_footballer->f_name<<",Match ID: "<<match_id_array[t]<<'\n';
				}
			}
			else{															/* For Hat-Trick command.*/
	
				if(goal_count > 2){
					output <<temp_pointer_footballer->f_name<<'\n';
				}
				
			}
		}
		
		temp_pointer_match = temp_pointer_footballer->next_match;
		
			
	}
	free(temp_pointer_footballer);
	return 0;
}




int main(int argc, char** argv){
	

	struct footballer *head_of_footballer = NULL ;   	/* Start with empty list.*/

  	string line;
  	ifstream myfile (argv[1]);			
  	ofstream output (argv[3]);
	vector<string> lines;		/* Creates a string vector for holding the lines of the input file.*/
	
  	if (myfile.is_open()){			/* If first file can open.*/
	
	  	int x = 0;				/* Line counter.*/
  	
	  	int counter_for_first_half = 0;
		int counter_for_second_half = 0;
		
  		while ( getline (myfile,line) ){	/* For assigning the lines from the input file to the string vector.*/  
  			lines.push_back(line);
  			x++;
		}	
		
  		stable_sort(lines.begin(), lines.end(), first_word());		/* For sorting the lines.*/

		
		int y = 0;
		vector<string> previous_footballers;  	/* Holds the footballers' names which came before.*/ 
		int footballer_count = 0;				/* For counting the footballers.*/
		
		int min, id;
		
		goal_score *sdc = new goal_score[x+1];
		
		
  		while (x != 0)
  		
   		{	
     
      
  			vector<string> v;

   			split(lines[y], ',', v);
				
			int i;
  	
 
  		 	char name[100];
			char team[100];
			char away[100];
  	
  		 	strcpy(name, v[0].c_str());			/* Assigns the footballer's name to name char array.*/
  		 	strcpy(team , v[1].c_str());			/* Assigns the footballer's team name to team char array.*/
  		 	strcpy(away , v[2].c_str());			/* Assigns the footballer's away team name to away char array.*/
		    sscanf(v[3].c_str(), "%d", &min);			/* Converts the min of goal value to integer and assigns it to integer min.*/
		    sscanf(v[4].c_str(), "%d", &id);			/* Converts the match id value to integer and assigns it to integer id.*/
	
			if (y == 0){									/* If first footballer comes.*/
				
				strcpy(sdc[footballer_count].scorer_name, name);			/* Fills the struct goal_score.*/ 
				strcpy(sdc[footballer_count].scorer_team , team);
				sdc[footballer_count].score_count = 1;
				previous_footballers.push_back(name);							/* Append the footballer's name to the previous_footballers vector.*/
				create_head(&head_of_footballer, name, team, away, min, id);		/* Creates the head of the linked list.*/
				
	
			}
			else if ( std::find(previous_footballers.begin(), previous_footballers.end(), string(name)) != previous_footballers.end() ){		/* If the footballer already exists in the linked list.*/
				
				for(int u = 0; u < (footballer_count+1) ; u++){
					if(string(sdc[u].scorer_name) == string(name)){		
						sdc[u].score_count ++;								/* Increment the footballer's goal count.*/
					} 
				}				
				if(min <= 45){
					counter_for_first_half++;		/* For finding the period in which the most goals are scored in the league, If the period is first.*/
				}
				else{								/* If the period is second.*/
					counter_for_second_half++;
				}						
				
		
				append_to_list(&head_of_footballer, name, team, away, min, id, 1);		/* Append a match node for a footballer's matches doubly linked list.*/
			
		
			}
			else{
			
				int l = 0;
				for(int u = 0; u < (footballer_count+1) ; u++){
					if(string(sdc[u].scorer_name) == string(name)){								/* Controls the name and the surnames are same.*/
						append_to_list(&head_of_footballer, name, team, away, min, id, 1);		/* If those are same then the parameter must be 1.*/
						l = 1;
					}
				}
				
				if( l == 0){						/* If the name and the surnames are not same.*/
					if(min <= 45){
						counter_for_first_half++; 		/* For finding the period in which the most goals are scored in the league, If the period is first.*/
					}
					else{
						counter_for_second_half++;		/* If the period is second.*/
					}
					
					append_to_list(&head_of_footballer, name, team, away, min, id,0);	/* Append a footballer node to the linked list.*/
					
					footballer_count ++;				/* Creates a new footballer for goal_score struct.*/ 
					strcpy(sdc[footballer_count].scorer_name , name);			/* Assigns the footballer's name.*/
					strcpy(sdc[footballer_count].scorer_team , team);			/* Assigns the footballer's team name.*/
					sdc[footballer_count].score_count = 1;						/* Makes the footballer's goal count 1.*/
					
				}
				
						
					previous_footballers.push_back(name);			/* Adds the current footballer's name to the string vector.*/
					
				}
				
	
      		x--;				/* Iterator and counters.*/
      		y++;	
      	

      		
   		}
   		
   		if(counter_for_first_half > counter_for_second_half ){
   			output << "1)THE MOST SCORED HALF\n0\n";
		}
   		else if(counter_for_first_half < counter_for_second_half){
   			output << "1)THE MOST SCORED HALF\n1\n";
		}
		else {
			output << "1)THE MOST SCORED HALF\n-1\n";
		}
   		
   		
   		output <<"2)GOAL SCORER\n" ;
   		
		int high = 0;
		
		for (int k = 0; k< footballer_count ; k++){
			if (sdc[k].score_count > high){
				high = sdc[k].score_count; 				/* Finds the top goal score.*/
			}
		}			
		for (int k1 = 0; k1< footballer_count ; k1++){
			if(sdc[k1].score_count == high){				/* Finds the footballer or footballers which can reach top goal score.*/
				output << sdc[k1].scorer_name << '\n';		/* Prints the footballer or footballers.*/
			}
		}
   		  		
   		output <<"3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK\n" ;
		char array[20]= "Hat Trick"	;	
   		order_match(output,&head_of_footballer,array, 2);
   		
   		output <<"4)LIST OF TEAMS\n";
   		team_list(output,&head_of_footballer);
   		
   		output << "5)LIST OF FOOTBALLERS\n";
 		for (int k = 0; k< footballer_count+1 ; k++){
 			output << sdc[k].scorer_name << '\n';	
		}
		string operations_line;
		int row = 0;
		vector<string> operations_lines;
		ifstream myfile2 (argv[2]);
			if (myfile2.is_open()){
				
				getline(myfile2,operations_line);
				vector<string> k;
   				split(operations_line, ',', k);			
   				char name1[100];
   				
   				strcpy(name1, k[0].c_str());
   				
				output <<"6)MATCHES OF GIVEN FOOTBALLER\n";				
				matches_of_footballers(output,&head_of_footballer,name1);
				strcpy(name1, k[1].c_str());
				matches_of_footballers(output,&head_of_footballer,name1);
				
				output <<"7)ASCENDING ORDER ACCORDING TO MATCH ID\n";
				getline(myfile2,operations_line);
				vector<string> k1;
   				split(operations_line, ',', k1);	
   				char name2[100];
   				strcpy(name2, k1[0].c_str());				
   				order_match(output,&head_of_footballer, name2, 0);
   				strcpy(name2, k1[1].c_str());
   				order_match(output,&head_of_footballer, name2, 0);
   				
   				output <<"8)DESCENDING ORDER ACCORDING TO MATCH ID\n";
   				getline(myfile2,operations_line);
				vector<string> k2;
   				split(operations_line, ',', k2);	
   				char name3[100];
   				strcpy(name3, k2[0].c_str());				
   				order_match(output,&head_of_footballer, name3, 1);			
   				strcpy(name3, k2[1].c_str());  				
   				order_match(output,&head_of_footballer, name3, 1);
   				
			}
			else{
				cout << "operations.txt not found" ;
			}	
   		

   		myfile.close();
		myfile2.close();
		output.close();
 	}

  else cout << "Unable to open file"; 


	


	
	return 0;
}
