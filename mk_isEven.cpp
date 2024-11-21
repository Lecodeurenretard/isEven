#include <cstdint>
#include <iostream>
#include <fstream>

#define EXIT_DOC -1			//The programs prints the doc
//#define EXIT_FAILURE  1	//The program exited for an unknown cause
//#define EXIT_SUCCESS 0	//Flawless execution
#define EXIT_415  2			//The program doesn't understand the user


//defining macros for colors
#define COLOR_RESET "\033[0m"

#define RED_FG     "\x1B[31m"
#define YELLOW_FG  "\x1B[33m"
#define MAGENTA_FG "\x1B[35m"
#define CYAN_FG    "\x1B[36m"
#define WHITE_FG   "\x1B[37m"

#define BBLACK_FG   "\x1B[90m"
#define BMAGENTA_FG "\x1B[95m"

#define RED_BG    "\033[3;41;30m"
#define YELLOW_BG "\033[3;43;30m"
#define BLACK_BG  "\033[3;100;30m"
#define CODE_STYLE BLACK_BG << WHITE_FG
#define VERBOSE_STYLE BMAGENTA_FG

void displayVerbose(std::string message, const bool& printVerbose){
	if(printVerbose){
		std::cout << VERBOSE_STYLE << message << "\r\n" << COLOR_RESET;
	}
}

int main(int argc, char *argv[]){
	int toTest(0);			//will test this at the end of the program
	unsigned int untilNum(1000);	//continues until this number (included)
	const bool printVerbose = (std::string(argv[argc-1]) == "--verbose") 
							|| (std::string(argv[argc-1]) == "-v");			//is last arg "--verbose"?
	

	if(printVerbose){	//modify the argument variables so the rest of the program don't get confused by the verbose arg
		argc--;
		argv[argc] = new char('\0');
	}
	
	//handles documentation
	displayVerbose("Check if should print doc...", printVerbose);

	std::string firstArg; 
	if (argc == 1){
		std::cout << "Enter the amount of tests to write (0 and this max amount counts too) or 'doc' to see the documentation: ";
		std::cin  >> firstArg;
	}else{
		firstArg = std::string(argv[1]);
	}
	

	if(firstArg == "doc" || firstArg == "-h" || firstArg == "--help"){
		std::cout 	<< YELLOW_BG << "USAGE:" << COLOR_RESET												<< std::endl
					<< "\t -" << CODE_STYLE << "'mk_isEven ((+|-)?\\d ){0,2}\\d?'\t\t" 				<< COLOR_RESET 	<<  "  -------->  Write a program that checks if a number is even (the if...else way for maximum efficiency!)"					<< std::endl
					<< "\t -" << CODE_STYLE << "'mk_isEven ((+|-)?\\d ){0,2}\\d? (--verbose|-v)'" 	<< COLOR_RESET 	<<  "  -------->  Same as previous but prints verbose."																			<< std::endl
					<< "\t -" << CODE_STYLE << "'mk_isEven (doc|-h|--help)'\t\t\t" 					<< COLOR_RESET 	<<  "  -------->  Prints this help and returns EXIT_DOC" 																		<< std::endl
																																																													<< std::endl
																																																													<< std::endl
				 	<< YELLOW_BG << "Parameters:" << COLOR_RESET																																													<< std::endl
					<< "\t-" << YELLOW_FG << "1st parameter" << COLOR_RESET << " " << MAGENTA_FG << "(int|str)" << COLOR_RESET << " " << CYAN_FG << "== " << " ~" << COLOR_RESET << ": If is an positive interger is passed, the number of tests to use; If is an negative number is passed, prints the default amount." 																<< std::endl
					<< "\t-" << YELLOW_FG << "2nd parameter" << COLOR_RESET << " " << MAGENTA_FG << "(int)    " << COLOR_RESET << " " << CYAN_FG << "== " << "-1" << COLOR_RESET << ": If an positive integer (including 0) is passed, the number to test just after creating the python script. \r\nElse it will not include the code to run the function at the end of the script."		<< std::endl
																																																													<< std::endl
				 	<< YELLOW_BG << "Exit codes:" << COLOR_RESET																																													<< std::endl
					<< "\t-" << YELLOW_FG << "EXIT_DOC\t" 		<< CYAN_FG << "== "   << EXIT_DOC		<< COLOR_RESET << ": The program printed this documentation."																				<< std::endl
					<< "\t-" << YELLOW_FG << "EXIT_SUCCESS\t" 	<< CYAN_FG << "==  "  << EXIT_SUCCESS 	<< COLOR_RESET << ": The program executed just fine."																						<< std::endl
					<< "\t-" << YELLOW_FG << "EXIT_FAILURE\t" 	<< CYAN_FG << "==  "  << EXIT_FAILURE 	<< COLOR_RESET << ": The program exited because of an unknown cause." 																		<< std::endl
					<< "\t-" << YELLOW_FG << "EXIT_415\t" 		<< CYAN_FG << "==  "  << EXIT_415		<< COLOR_RESET << ": The program didn't understood an argument." 																			<< std::endl;
		return EXIT_DOC;
	}
	
	//setting vars
	displayVerbose("Setting up vars and opening python script file...", printVerbose);

	try{
		untilNum = std::stoi(firstArg);
	}catch(const std::invalid_argument& e){
		std::cerr << RED_BG <<"No conversion could be performed by std::stoi() on the first argument, please input a number.\r\n" << COLOR_RESET;
		return EXIT_415;
	}catch(const std::out_of_range& e){
		std::cerr << RED_BG << "Please input a number less than 2^32 (or " << 0xFFFFFFFF << ") for the first argument.\r\n" << COLOR_RESET;
		return EXIT_FAILURE;
	};

	std::ofstream script;
	script.open("isEven.py");

	//imports
	displayVerbose("Writing the first bit of code (imports, variables def, etc)...", printVerbose);

	script << "import sys"													<< std::endl
																			<< std::endl;

	//defines the function and documentates it with a docstring
	#define DOCQUOTES "\"\"\""		//It's just ugly
	script 	<< "def is_even(n : int) -> bool:" 								<< std::endl 
			<< "\t"
			<< DOCQUOTES 
			<< "Checks if the number is even, n must be strictly below " 			<< std::to_string(untilNum) << '.'
			<< DOCQUOTES 													<< std::endl;

	//making sure n is an int bc Python is a language where staticly type is useless
	script << "\tn = abs(int(n))\t\t# This is another reason to dislike python"	<< std::endl
	 																		<< std::endl;

	//prints the program, the first line is separated so we don't have to check each time if it's 0 (writing faster a slow code, isn't it Python's philosophy?)
	displayVerbose("Writing the principal part of the code (if...else)...", printVerbose);

	script	<< "\tif(n == 0):" 												<< std::endl
	 		<< "\t\treturn True"											<< std::endl;
	for(unsigned int i = 1; i <= untilNum-1; i++){
		if(i%2 == 1){
			script << "\telif(n == " << std::to_string(i) << "):" 				<< std::endl;
			script << "\t\treturn False"										<< std::endl;
			continue;
		}
		
		script << "\telif(n == " << std::to_string(i) << "):" 			<< std::endl;
		script << "\t\treturn True"											<< std::endl;
	}
	script	<< "\treturn False" 											<< std::endl
																			<< std::endl;
	
	
	//writing script that calls the function
	if(argc >= 3){
		displayVerbose("Check if should write last part of the code...", printVerbose);
		
		unsigned int last_arg;
		try{
			last_arg = std::stoi(argv[2]);
		}catch(const std::invalid_argument& e){
			std::cerr << RED_BG <<	"No conversion could be performed by std::stoi() on the second argument, please input a number.\r\n" << COLOR_RESET;
			return EXIT_415;
		}catch(const std::out_of_range& e){
			std::cerr << RED_BG << "Please input a number less than 2^32 (" << 0xFFFFFFFF << ") and more than -" << 0xFFFFFFFF/2 << " for the second argument.\r\n" << COLOR_RESET;
			return EXIT_FAILURE;
		}
		
		if(std::stoi(argv[2]) < 0)
			goto endLabel;

		displayVerbose("Writing last bit of code (function calls)...", printVerbose);
		script	<< "# Calls the function with the first cmd line arg"		<< std::endl
				<< "if(len(sys.argv) >= 1):" 								<< std::endl
				<< "\tprint(is_even(sys.argv[1]))";
		
	}
	
	endLabel:
		displayVerbose("Closing file...", printVerbose);
		script.close();	

		//executes the script 
		if(toTest != -1 && argc >= 3){
			displayVerbose("Running commands...", printVerbose);

			std::string command("python3 isEven.py ");
			command.append(argv[2]);
			std::system(command.c_str());
		}

		displayVerbose("Done!", printVerbose);
		return EXIT_SUCCESS;
}