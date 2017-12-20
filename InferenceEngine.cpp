#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
#include<fstream>
#include <ctype.h>
#include <algorithm> 
using namespace std;

int NQ;
int NS;
vector<string> queries;
int countVariable = 1;


vector<bool> answers;

class Predicate{
public:
	string name;
	bool isNegate;
	std::map<std::string, string> args;
	vector<string> argsOrder;
	int position = -1;
	int totalUnified = 0;
	int constCount = 1;
	int unifyCounter = 0;
	int localUnified = 0;
	int clauseNum =0;

	Predicate()
	{
		name = "";
		isNegate = false;
	}

	Predicate(string pname, bool pisNegate,std::map<std::string, string> arguments)
		{
				name = pname;
				isNegate	 = pisNegate;
				args = arguments;
		}


};

class Clause{
public:
	Clause(){

	}
	std::vector<Predicate> cl;
	Clause(std::vector<Predicate> clP){
		cl = clP;
	}

};

//positive
std::map<std::string, std::vector<Clause> > pKnowledgeBase;
//negative
std::map<std::string, std::vector<Clause> > nKnowledgeBase;
//to store counter values
std::map<std::string, int> nCounterMap;
//to store counter values
std::map<std::string, int> pCounterMap;

bool unification(std::vector<Predicate> argResultLHS,int depth,int k,std::map<std::string, std::vector<Clause> > tempPKnowledgeBase, std::map<std::string, std::vector<Clause> > tempNKnowledgeBase)
{
	k = argResultLHS.size();
	if(depth>200){
		return false;
	}
		//positive
	//	std::map<std::string, std::vector<Clause>> tempPKnowledgeBase;
		//negative
	//	std::map<std::string, std::vector<Clause>> tempNKnowledgeBase;
	//	tempPKnowledgeBase = pKnowledgeBase;
	//	tempNKnowledgeBase = nKnowledgeBase;
//	 for( std::map<std::string, std::vector<Clause>>::iterator itp=pKnowledgeBase.begin(); itp!=pKnowledgeBase.end(); ++itp)
//		  {
//
//			   	 for(int l = 0; l < itp->second.size(); l++){
//			   		 if(itp->second[l].cl[0].localUnified >5)
//			   			itp->second[l].cl[0].localUnified =  tempPKnowledgeBase[itp->first][l].cl[0].localUnified;
//			   		// itp->second[l].cl[0].localUnified = 0;
//			   	 }
//		   }
//		  for( std::map<std::string, std::vector<Clause>>::iterator itn=nKnowledgeBase.begin(); itn!=nKnowledgeBase.end(); ++itn)
//		  {
//
//			  	  for(int l = 0; l < itn->second.size(); l++) {
//			  		if(itn->second[l].cl[0].localUnified >5)
//			  			itn->second[l].cl[0].localUnified =  tempNKnowledgeBase[itn->first][l].cl[0].localUnified;
//			  		// itn->second[l].cl[0].localUnified = 0;
//			   	 }
//		  }
	std::vector<Predicate> resultLHS = argResultLHS;
	std::map<std::string, vector<Clause> > tempKnowledgeBase;

	if(k>resultLHS.size())
		{
			return false;
		}

	std::map<string,vector<Clause> >::iterator it;

while(resultLHS.size()>1 && k>1)
{
	k = k-1;
	bool canUnify = false;
	  if(resultLHS[k].isNegate)
	  {
		  tempKnowledgeBase = pKnowledgeBase;
	  }
	  else
	  {
		  tempKnowledgeBase = nKnowledgeBase;
	  }

	it = tempKnowledgeBase.find(resultLHS[k].name);
	  if (it != tempKnowledgeBase.end())
		{

		  //Unification step
		  //check if this can be unified
		  //and if yes then unify and add the unified clause to the KB
		  int unifyCount=0;
		  int unifyCountloops = 0;

		  	  if(resultLHS[k].isNegate)
		 			  {
			  	  	  	  std::map<std::string, int>::iterator itMap = pCounterMap.find(resultLHS[k].name);
					  	  if (itMap != pCounterMap.end())
					  	  {
					  		pCounterMap[it->first] = pCounterMap[it->first] + 1;
					  		pCounterMap[it->first] = pCounterMap[it->first] % it->second.size();
					  		unifyCount =  pCounterMap[it->first];
					  	  }
					  	  else
					  		pCounterMap[it->first] = 0;
					  	  	unifyCount =  pCounterMap[it->first];
		 			  }
		 	  else
		 			  {
		 				  std::map<std::string, int>::iterator itMap = nCounterMap.find(resultLHS[k].name);
		 				  if (itMap != nCounterMap.end())
		 				  {
		 					  nCounterMap[it->first] = nCounterMap[it->first] + 1;
		 					  nCounterMap[it->first] = nCounterMap[it->first] % it->second.size();
		 					  unifyCount =  nCounterMap[it->first];
		 				  }
		 				  else
		 					  nCounterMap[it->first] = 0;
		 				  	  unifyCount =  nCounterMap[it->first];

		 			  }
		  while(!canUnify && unifyCountloops<it->second.size()){
			 if(it->second[unifyCount].cl[0].totalUnified > 300 || it->second[unifyCount].cl[0].localUnified >  NS * 10 )
			  {
				 if(resultLHS[k].isNegate)
				 		 			  {
					 	 	 	 	 	  pKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
					 	 	 	 	 	  pKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
				
					 	 	 	 	// 	  tempPKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
					 	 	 	 	 
					 	 	 	 	// 	  tempPKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
					 	 	 	 	 
				 		 				  pCounterMap[it->first] = pCounterMap[it->first] + 1;
				 		 				
				 		 				  pCounterMap[it->first] = pCounterMap[it->first] % it->second.size();
				 		 				
				 		 				  unifyCount =  pCounterMap[it->first];
				 		 				
				 		 			  }
				 		 			  else
				 		 			  {
				 		 				  nKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
				 		 				
				 		 				  nKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
				 		 				
					 	 	 	 	 	//  tempNKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
					 	 	 	 	 
					 	 	 	 	 //	  tempNKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
					 	 	 	 	 	
				 		 				  nCounterMap[it->first] = nCounterMap[it->first] + 1;
				 		 				
				 		 				  nCounterMap[it->first] = nCounterMap[it->first] % it->second.size();
				 		 				
				 		 				  unifyCount =  nCounterMap[it->first];
				 		 				
				 		 			  }
				 unifyCountloops++;
				 continue;
			  }
			 
			  //Check if its constant or a variable

			  std::map<std::string, std::string> nameStandardize;
			  std::vector<Predicate> resultRHS = it->second[unifyCount].cl;
			  for(int o = 0; o< resultLHS[k].argsOrder.size();o++)
			  {

				  string itLHSfirst = resultLHS[k].argsOrder[o];
				  string itLHSsecond = resultLHS[k].args[resultLHS[k].argsOrder[o]];
				  string itRHSfirst = resultRHS[resultRHS[0].position].argsOrder[o];
				  string itRHSsecond = resultRHS[resultRHS[0].position].args[resultRHS[resultRHS[0].position].argsOrder[o]];
				  //if both are different constants then can't be unified else can be unified.
				 
				  if(isdigit(itLHSfirst[0]) && isdigit(itRHSfirst[0]) && (itLHSsecond != itRHSsecond))
				  {
					  canUnify = false;
					  break;
				  }
				  else if(isdigit(itLHSfirst[0]) && isdigit(itRHSfirst[0]) && (itLHSsecond == itRHSsecond))
				  {
					  canUnify = true;
				  }
				  else if(!isdigit(itLHSfirst[0]) && !isdigit(itRHSfirst[0])){
					  canUnify = true;
				  }
				  else if(isdigit(itLHSfirst[0]) && !isdigit(itRHSfirst[0]) )
				  {
					  nameStandardize[itRHSfirst] = itLHSsecond;
					  canUnify = true;
				  }
				  else
				  {
					  nameStandardize[itLHSfirst] = itRHSsecond;
					  canUnify = true;
				  }
			  }
  			  if(resultLHS[k].isNegate)
  			  {
  				  pKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
  				  pKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
  			     // tempPKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
  			//	  tempPKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
  			  }
  			  else
  			  {
  				  nKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
  				  nKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
  			   //   tempNKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].totalUnified++;
  				//  tempNKnowledgeBase[resultLHS[k].name][unifyCount].cl[0].localUnified++;
  			  }

  			  if(resultLHS[k].isNegate)
			  {
				  pCounterMap[it->first] = pCounterMap[it->first] + 1;
				  pCounterMap[it->first] = pCounterMap[it->first] % it->second.size();
				  unifyCount =  pCounterMap[it->first];
			  }
			  else
			  {
				  nCounterMap[it->first] = nCounterMap[it->first] + 1;
				  nCounterMap[it->first] = nCounterMap[it->first] % it->second.size();
				  unifyCount =  nCounterMap[it->first];
			  }

			  if(canUnify){

				  resultLHS.erase(resultLHS.begin()+k);
				  resultRHS.erase(resultRHS.begin()+resultRHS[0].position);
				  resultRHS.erase(resultRHS.begin());

				  //check if there are predicates in the resultant clause which could be resolved
				  for(int t = 1; t<resultLHS.size();t++)
				  {
					  for(int w = 0; w<resultRHS.size();w++)
					  {
					  	if(resultLHS[t].name == resultRHS[w].name && resultLHS[t].isNegate != resultRHS[w].isNegate)
					  	{
					  		bool canUnifySameClause = false;
					  		for(int o = 0; o< resultLHS[t].argsOrder.size();o++)
					  					  {

					  						  //move this logic to a function
					  						  string itLHSfirst = resultLHS[t].argsOrder[o];
					  						  string itLHSsecond = resultLHS[t].args[resultLHS[t].argsOrder[o]];
					  						  string itRHSfirst = resultRHS[w].argsOrder[o];
					  						  string itRHSsecond =  resultRHS[w].args[resultRHS[w].argsOrder[o]];

					  						  //if both are different constants then can't be unified else can be unified.
					  						  if(isdigit(itLHSfirst[0]) && isdigit(itRHSfirst[0]) && (itLHSsecond != itRHSsecond))
					  						  {
					  							  canUnifySameClause = false;
					  							  break;
					  						  }
					  						  else if(isdigit(itLHSfirst[0]) && isdigit(itRHSfirst[0]) && (itLHSsecond == itRHSsecond))
					  						  {
					  							  canUnifySameClause = true;
					  						  }
					  						  else if(!isdigit(itLHSfirst[0]) && !isdigit(itRHSfirst[0]))
					  						  {
					  							  canUnifySameClause = true;
					  						  }
					  						  else if(isdigit(itLHSfirst[0]) && !isdigit(itRHSfirst[0]) )
					  						  {
					  							  nameStandardize[itRHSfirst] = itLHSsecond;
					  							  canUnifySameClause = true;
					  						  }
					  						  else
					  						  {
					  							  nameStandardize[itLHSfirst] = itRHSsecond;
					  							  canUnifySameClause = true;
					  						  }
					  					  }
					  		if(canUnifySameClause){
					  			resultLHS.erase(resultLHS.begin()+t);
					  			resultRHS.erase(resultRHS.begin()+w);
					  		}

					  	}
					  }
				  }

				  //appending resultLHS to resultRHS
				  resultLHS.insert(std::end(resultLHS), std::begin(resultRHS), std::end(resultRHS));


			  }


			  if(resultLHS.size() ==1)
			  {
				  return true;
			  }

			  //assigning the unified values
			  if(canUnify){
			  for(int i =1; i<resultLHS.size();i++){
				  std::map<std::string, string> argsUpdated;
				 for(std::map<string,string>::iterator itr=resultLHS[i].args.begin(); itr!=resultLHS[i].args.end(); ++itr){
					  if(nameStandardize.find(itr->first) != nameStandardize.end() && nameStandardize[itr->first] != ""){
						  string constant = nameStandardize[itr->first];
						  string num = to_string(resultLHS[i].constCount);
						  resultLHS[i].constCount++;
						  std::vector<string>::iterator itOrder;
						  //updating the value in the order array
						  itOrder = find (resultLHS[i].argsOrder.begin(), resultLHS[i].argsOrder.end(),itr->first);
						  if (itOrder != resultLHS[i].argsOrder.end())
							  *itOrder = num;
						  argsUpdated[num] = constant;
					  }
					  else
						  {
						  	  argsUpdated[itr->first] = itr->second;
						  }
			  }
				 resultLHS[i].args = argsUpdated;
			  }
//			  for(int i =1; i<resultLHS.size();i++){
//				  resultLHS[0].position = i;
//				  resultLHS[0].totalUnified = 0;
//				  resultLHS[0].localUnified = 0;
//				  resultLHS[0].unifyCounter = 0;
//				  //adding new clauses to the KB //see if this step is needed.
//				  if(resultLHS[i].isNegate){
//					  nKnowledgeBase[resultLHS[i].name].push_back(Clause(resultLHS));
//				 }
//				  else
//				 {
//					  pKnowledgeBase[resultLHS[i].name].push_back(Clause(resultLHS));
//				 }
//
//			  }
			}
			  unifyCountloops++;
			  if(canUnify)
			  {

				  bool answer = unification(resultLHS,depth+1,k,tempPKnowledgeBase,tempNKnowledgeBase);
				  if(answer)
				  {
					  return true;
				  }
				  else
					  {
					  	  canUnify = false;
					  	  resultLHS.clear();
					  	  resultLHS = argResultLHS;
					  //	  pKnowledgeBase = tempPKnowledgeBase;
					  //	  nKnowledgeBase = tempNKnowledgeBase;

					  	 // if(k > resultLHS.size()-1)
					  		 // break;
					  }
			  	  }

		  }
	}

	//  k = k-1;

} //end of inner while

	return false;
}


int main(){

	   fstream inputFile;
	   ofstream outputFile;

	   inputFile.open("./input.txt");
	   if (inputFile.is_open())
	   {
	       string line;

	       getline(inputFile, line);       // Number of Queries
	       NQ = stoi(line);

	       for(int i =0;i<NQ;i++)
	       {
	    	   	   	   getline(inputFile, line);       //Reading the queries
	    	   	   	   queries.push_back(line);
	       }


	       getline(inputFile, line);       //Number of Statements
	       NS = stof(line);

	       for (int i = 0; i < NS; i++)
	       {

	           getline(inputFile, line);
	           string stmt = line;

	           //Code to store the statements in the KB dictionary

	           std::size_t pos = 0, found=0;

	           //Also add a check for "OR" operator
	           int j =0;
	           std::vector<Predicate> cl;
	           cl.push_back(Predicate());

	           //Check if its constant or a variable
	           std::map<std::string, std::string> nameStandardize;

	           while((found = stmt.find_first_of('|', pos)) != std::string::npos || pos < stmt.length()) {
	        	   	 Predicate predicate;
	        	   	 //test if the clausecopy is being updated once the clause is update
	        	   	// Clause* clauseCopy = &clause;
	        	   	 string key ="";
	        	   	 if(found != -1)
	        	   		 key = stmt.substr(pos, found-pos-1);
	        	   	 else
	        	   		 key = stmt.substr(pos);

	        	   	 //parsing the predicate to find out the name of the predicate and the arguments
	        	   	std::size_t begin = 0,end = 0;
	        	   	string pName="";
	        	   	string argName="";
	        	   	//predicate name
	        	   	end = key.find_first_of('(', begin);
	        	   	pName = key.substr(begin,end);
	        	   	begin = end+1;
	        	   	//args
	        	   	while((end = key.find_first_of(',', begin)) != std::string::npos || begin < key.length()) {
	        	   	 if(end != -1)
	        	   		argName = key.substr(begin, end - begin);
	        	  	 else{
	        	  		end = key.find_first_of(')', begin);
	        	  		argName = key.substr(begin, end - begin);
	        	  	 }

	        	   	 string num = to_string(predicate.constCount);

	        	   	 if(argName.length() == 1)
	        	   		{if(islower(argName[0])) //means its a variable //single lower case letter
	        	   			{
	        	   				if(nameStandardize.find(argName) != nameStandardize.end()){
	        	   					string standardName = nameStandardize[argName];
	        	   					argName = standardName;
	        	   				}
	        	   				else{
	        	   					string standardName = "x"+ to_string(countVariable);
	        	   					countVariable++;
	        	   					nameStandardize[argName] = standardName;
	        	   					argName = standardName;
	        	   				}
	        	   				predicate.args[argName] = "";
	        	   				predicate.argsOrder.push_back(argName);//put empty string till the variable is substituted
	        	   			}
	        	   		else
	        	   			{
	        	   				predicate.args[num] = argName; //save the variable name with the argument number
	        	   				predicate.constCount++;
	        	   				predicate.argsOrder.push_back(num);//and its value
	        	   			}
	        	   		}
	        	   	 else{
	        	   		predicate.args[num] = argName;
	        	   		predicate.constCount++;
	        	   		predicate.argsOrder.push_back(num);
	        	   	 }
	        	   	if(end != -1)
	        	   		begin = end+1;
	        	   	else
	        	   		break;

	        	   	}


	        	   	 //add a check for "NOT" string as well

	        	   	 if(key[0] == '~')
	        	   	 {
	        	   		pName.erase (pName.begin());
	        	   		predicate.isNegate = true;
	        	   		predicate.name = pName;
	        	   		predicate.position = j;

	        	   	 }
	        	   	 else
	        	   	 {
	        	   		predicate.isNegate = false;
	        	   		predicate.name = pName;
	        	   		predicate.position = j;

	        	   	 }
	        	   	cl.push_back(predicate);
	        	   	if(found != -1)
	        	   		pos = found+2;
	        	   	else
	        	   		break;
	        	   		j++;
	           }

	        	   	 //can this cost be reduced????
	        	   	for(std::vector<int>::size_type i = 1; i < cl.size(); i++) {
	        	   	    Predicate p = cl[i];
	        	   	    cl[0].position = i;
	        	   	    cl[0].totalUnified = 0;
	        	   	    cl[0].localUnified = 0;
	        	   	    if(p.isNegate)
	        	   	    {
	        	   	    		nKnowledgeBase[p.name].push_back(Clause(cl));
	        	   	    }
	        	   	    else
	        	   	    {
	        	   	    		pKnowledgeBase[p.name].push_back(Clause(cl));
	        	   	    }
	        	   	}
	       }
	       inputFile.close();
	   }


	//Answering the queries
	//length = pKnowledgeBase.size();
	for(int i = 0; i<queries.size(); i++)
	{
		//clearing up all the parameters for every query

		//positive
		std::map<std::string, std::vector<Clause> > tempPKnowledgeBase;
		//negative
		std::map<std::string, std::vector<Clause> > tempNKnowledgeBase;
		tempPKnowledgeBase = pKnowledgeBase;
		tempNKnowledgeBase = nKnowledgeBase;


		 pCounterMap.clear();
		 nCounterMap.clear();
		 for( std::map<std::string, std::vector<Clause> >::iterator itp=pKnowledgeBase.begin(); itp!=pKnowledgeBase.end(); ++itp)
		  {
			   	 for(int l = 0; l < itp->second.size(); l++) {
			   		 itp->second[l].cl[0].totalUnified = 0;
			   		 itp->second[l].cl[0].localUnified = 0;
			   	 }
		   }
		  for( std::map<std::string, std::vector<Clause> >::iterator itn=nKnowledgeBase.begin(); itn!=nKnowledgeBase.end(); ++itn)
		  {
			  	  for(int l = 0; l < itn->second.size(); l++) {
			  		 itn->second[l].cl[0].totalUnified = 0;
			  		 itn->second[l].cl[0].localUnified = 0;
			   	 }
		  }
		string query = queries[i];

					std::vector<Predicate> resultLHS;
					resultLHS.push_back(Predicate());
					resultLHS.push_back(Predicate());

					if(query[0] == '~')
							{
								query.erase (query.begin());
								resultLHS[1].isNegate = false;
							}
							else
								resultLHS[1].isNegate = true;
				//TODO: create  function for this code
				//parsing the predicate to find out the name of the predicate and the arguments
	        	   	std::size_t begin = 0,end = 0;
	        	   	string pName="";
	        	   	string argName="";
	        	   	//predicate name
	        	   	end = query.find_first_of('(', begin);
	        	   	pName = query.substr(begin,end);

	        	   	begin = end+1;
	        	   	//args
	        	   	while((end = query.find_first_of(',', begin)) != std::string::npos || begin < query.length()) {
	        	   	 if(end != -1)
	        	   		argName = query.substr(begin, end - begin);
	        	  	 else{
	        	  		end = query.find_first_of(')', begin);
	        	  		argName = query.substr(begin, end - begin);
	        	  	 }

	        	   	string num = to_string(resultLHS[1].constCount);
	        	   	 //Check if its constant or a variable
	        	   	 if(argName.length() == 1)
	        	   	 {	if(islower(argName[0])) //means its a variable //single lower case letter
	        	   			{
	        	   				argName = "x" + to_string(countVariable);
	        	   				countVariable++;
	        	   				resultLHS[1].args[argName] = "";
	        	   				resultLHS[1].argsOrder.push_back(argName);//put empty string till the variable is substituted
	        	   			}
	        	   		else
	        	   			{
	        	   				resultLHS[1].args[num] = argName; //save the variable name with the argument number
	        	   				resultLHS[1].constCount++;
	        	   				resultLHS[1].argsOrder.push_back(num);
	        	   			}
	        	   	 } 	 	 	 	 	 	 	 	 	 	 	 	 	//and its value
	        	   	 else
	        	   		{
	        	   		 	 resultLHS[1].args[num] = argName;
	        	   		 	 resultLHS[1].constCount++;
	        	   		 	 resultLHS[1].argsOrder.push_back(num);
	        	   		}

	        	   	if(end != -1)
	        	   		begin = end+1;
	        	   	else
	        	   		break;

	        	   	}

					resultLHS[1].name = pName;
					//adding the query to the KB
					Predicate pquery = resultLHS[1];
					std::vector<Predicate> clQuery;
					clQuery.push_back(Predicate());
					clQuery[0].position = 1;
					clQuery[0].totalUnified = 0;
					clQuery[0].localUnified = 0;
					clQuery.push_back(pquery);
					if(pquery.isNegate)
						nKnowledgeBase[pquery.name].push_back(Clause(clQuery));
					else
						pKnowledgeBase[pquery.name].push_back(Clause(clQuery));

					//resolution step
					//UNIFICATION
					bool answer = unification(resultLHS,0,1,pKnowledgeBase,nKnowledgeBase);
					answers.push_back(answer);

					pKnowledgeBase = tempPKnowledgeBase;
					nKnowledgeBase = tempNKnowledgeBase;
		}

	  outputFile.open("./output.txt", ios::trunc);
	    if (outputFile.is_open()) {
	    	for(int i =0 ;i < answers.size() ; i++)
	    	{
	        	if(answers[i])
	    	    		 outputFile<<"TRUE"<<"\n";
	    	    	else
	    	    		outputFile<<"FALSE"<<"\n";
	    	}
	    	  outputFile.close();
	    	}


	return 0;
	}





