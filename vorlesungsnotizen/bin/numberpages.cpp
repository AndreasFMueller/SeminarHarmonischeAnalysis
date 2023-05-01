/*
 * numberpages.cpp -- driver program to number pages in a PDF, this was
 *                    mainly necessary because the shell breaks blanks
 *                    in the section option string
 *
 * (c) 2022 Prof Dr Andreas Müller, OST Ostschweizer Fachhochschule
 */
#include <cstdio>
#include <cstdlib>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>

void	usage(char *progname) {
	std::cout << "usage: " << progname << " [ -df ] [ -s section ] ";
	std::cout << "<unnumbered.pdf> <numbered.pdf>" << std::endl;
	std::cout << "options:" << std::endl;
	std::cout << " -d,--debug         enable debug mode" << std::endl;
	std::cout << " -h,-?,--help       show this help message" << std::endl;
	std::cout << " -n,--number=<n>    number of the section" << std::endl;
	std::cout << " -f,--force         overwrite output file" << std::endl;
	std::cout << " -s,--section=<s>   use <s> as the section title" << std::endl;
	std::cout << " -t,--title=<t>     use title <t>";
	std::cout << std::endl;
}

struct option	longoptions[] = {
{ "debug",	no_argument,		NULL,	'd' },
{ "help",	no_argument,		NULL,	'h' },
{ "section",	required_argument,	NULL,	's' },
{ "title",	required_argument,	NULL,	't' },
{ "force",	no_argument,		NULL,	'f' },
{ "number",	required_argument,	NULL,	'n' },
{ NULL,		no_argument,		NULL,	 0  }
};

bool	reserved(const std::string& name) {
	return (std::string::npos != name.find("numbered"));
}

int	main(int argc, char *argv[]) {
	bool	force = false;
	bool	debug = false;
	std::string	section;
	std::string	title;
	std::string	number;
	int	c, longindex, rc;
	while (EOF != (c = getopt_long(argc, argv, "dfhn:s:t:?", longoptions,
		&longindex))) {
		switch (c) {
		case 'd':
			debug = true;
			break;
		case 'f':
			force = true;
			break;
		case 'h':
		case '?':
			usage(argv[0]);
			return EXIT_SUCCESS;
		case 'n':
			number = std::string(optarg);
			break;
		case 's':
			section = std::string(optarg);
			if (debug) {
				std::cout << "section string: " << section;
				std::cout << std::endl;
			}
			break;
		case 't':
			title = std::string(optarg);
			if (debug) {
				std::cout << "title string: " << title;
				std::cout << std::endl;
			}
			break;
		}
	}
	if (0 == title.size()) {
		title = section;
	}

	// remaining arguments are file names
	if ((argc - optind) < 2) {
		std::cerr << "not enough arguments" << std::endl;
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	std::string	unnumbered = std::string(argv[optind++]);
	std::string	numbered = std::string(argv[optind++]);
	if (debug) {
		std::cout << "numbering " << unnumbered;
		std::cout << ", sending output to " << unnumbered;
		std::cout << std::endl;
	}

	// make sure the names are not reserved
	if (reserved(unnumbered)) {
		std::cerr << "cannot use filename " << unnumbered << std::endl;
		return EXIT_FAILURE;
	}
	if (reserved(numbered)) {
		std::cerr << "cannot use filename " << numbered << std::endl;
		return EXIT_FAILURE;
	}

	// make sure input file does exist
	struct stat	sb;
	rc = stat(unnumbered.c_str(), &sb);
	if ((0 == rc) && S_ISREG(sb.st_mode)) {
		if (debug) {
			std::cout << "input file " << unnumbered << " found";
			std::cout << std::endl;
		}
	} else {
		std::cerr << "cannot find " << unnumbered << std::endl;
		return EXIT_FAILURE;
	}

	// make sure the "unnumbered.pdf" file does not exist
	rc = stat("unnumbered.pdf", &sb);
	if (0 == rc) {
		unlink("unnumbered.pdf");
		std::cout << "warning: unnumbered.pdf has been removed";
		std::cout << std::endl;
	}

	// test for existence of output file
	rc = stat(numbered.c_str(), &sb);
	if ((!force) && (0 == rc)) {
		std::cerr << "output file exists, use --force option";
		std::cerr << std::endl;
		return EXIT_FAILURE;
	}

	// make sure the numbered.tex is present
	rc = stat("numbered.tex", &sb);
	if ((0 != rc) || (!S_ISREG(sb.st_mode))) {
		std::cerr << "file 'numbered.tex' is missing" << std::endl;
		std::cerr << "hint: run in 'bin' directory" << std::endl;
		return EXIT_FAILURE;
	}

	// remove the "numbered.pdf" if it exists
	if (debug) {
		std::cout << "removing numbered.pdf" << std::endl;
	}
	unlink("numbered.pdf");

	// copy the file
	{
		std::ostringstream	out;
		out << "cp '" << unnumbered << "' unnumbered.pdf";
		out.flush();
		std::string	copycommand = out.str();
		rc = system(copycommand.c_str());
		if (0 != rc) {
			std::cerr << "could not copy " << unnumbered;
			std::cerr << " to unnumbered.pdf: " << rc << std::endl;
			return EXIT_FAILURE;
		}
		if (debug) {
			std::cout << "file " << unnumbered << " copied to ";
			std::cout << "unnumbered.pdf" << std::endl;
		}
	}

	// prepare command line
	std::ostringstream	out;
	out << "pdflatex ";
	if (title.size() > 0) {
		out << "\\\\def\\\\titlestring{" << title << "} ";
	}
	if (section.size() > 0) {
		out << "\\\\def\\\\sectionnumber{" << section << "} ";
	}
	out << "\\\\def\\\\numberstring{" << number << "} ";
	out << "\\\\input{numbered.tex}";
	if (debug) {
		std::cout << "command line: " << out.str() << std::endl;
	}

	// run the command
	rc = system(out.str().c_str());
	if (0 != rc) {
		std::cerr << "pdflatex failed: " << rc << std::endl;
		return EXIT_FAILURE;
	}

	// check for the existence of the output file
	rc = stat("numbered.pdf", &sb);
	if ((0 != rc) || (!S_ISREG(sb.st_mode))) {
		std::cerr << "output file 'numbered.pdf' not found";
		std::cerr << std::endl;
		return EXIT_FAILURE;
	}

	// rename the output file
	rc = rename("numbered.pdf", numbered.c_str());
	if (rc != 0) {
		std::string	error(strerror(errno));
		std::cerr << "cannot rename file to '" << numbered << ": ";
		std::cerr << error << std::endl;
		return EXIT_FAILURE;
	}

	// perform some cleanup
	unlink("unnumbered.pdf");
	unlink("numbered.log");
	unlink("numbered.aux");

	return EXIT_SUCCESS;
}
