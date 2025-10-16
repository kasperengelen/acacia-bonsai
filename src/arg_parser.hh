#pragma once

#include <boost/program_options.hpp>

// TODO: why is there "do while()?"
#define debug_(A...) do { std::cout << A << std::endl; } while (0)

namespace po = boost::program_options;

/**
 * Struct that will hold the parsed argument values.
 */
struct ArgParseResult {

};

/**
 * Function that parses the arguments into a ArgParseResult object.
 *
 * @param argc The value of 'argc', as passed to main().
 * @param argv The value of 'argv', as passed to main().
 *
 * @return ArgParseResult object with the argument values.
 */
ArgParseResult arg_parser(int argc, char **argv) {
  debug_("Parsing arguments.");
  try {
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "print this help")
    ("version", "print program version")

    // ??
    ("f,formula", po::value<std::string>()->value_name("STRING"),
      "process the formula STRING")
    ("F,file", po::value<std::string>()->value_name("FILENAME[/COL]"),
      "process each line of FILENAME as a formula; if COL "
                                                "is a positive integer, assume a CSV file and read "
                                                "column COL; use a negative COL to drop the first "
                                                "line of the CSV file")
    ("lbt-input", po::bool_switch()->default_value(false),
      "read all formulas using LBT's prefix syntax")
    ("lenient", po::bool_switch()->default_value(false),
      "parenthesized blocks that cannot be parsed as "
                             "subformulas are considered as atomic properties")

    // input options
    ("0,init", po::value<std::string>()->value_name("STATE"),
      "comma-separated state vector to use as initial state")
    ("i,ins", po::value<std::string>()->value_name("PROPS"),
      "comma-separated list of uncontrollable (a.k.a. input) atomic propositions")
    ("j,workers", po::value<std::string>()->value_name("VAL"),
      "Number of parallel workers for composition")
    ("o,outs", po::value<std::string>()->value_name("PROPS"),
      "comma-separated list of controllable (a.k.a. output) atomic propositions")
    ("S,synth", po::value<std::string>()->value_name("FILENAME"),
      "enable synthesis, pass .aag filename, or - to print gates")
    ("W,winreg", po::value<std::string>()->value_name("FILENAME"),
      "output winning region, pass .aag filename, or - to print gates")

    // fine tuning
    ("I,Kinc", po::value<std::string>()->value_name("VAL"),
      "increment value for K, used when Kmin < K")
    ("K", po::value<std::string>()->value_name("VAL"),
      "final value of K, or unique value if Kmin is not specified")
    ("M,Kmin", po::value<std::string>()->value_name("VAL"),
      "starting value of K; Kinc MUST be set when using "
                             "this option")
    ("u,unreql-x", po::value<std::string>()->value_name("[formula|automaton|both]"),
      "for unrealizability, either add X's to outputs in "
                             "the input formula, or push outputs one transition "
                             "forward in the automaton; with 'both', two "
                             "processes are started, one for each option "
                             "(default: both).")

    // output options
    ("c,check", po::value<std::string>()->value_name("[real|unreal|both]"),
      "either check for real, unreal, or both")
    ("v,verbose", po::bool_switch()->default_value(false)->zero_tokens(),
      "verbose mode, can be repeated for more verbosity")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count ("help")) {
      std::cout << desc << std::endl;
      exit(0);
    }

    // TODO: extract information here

    return ArgParseResult();

  } catch (const std::exception& ex) {

    exit(3);
  }

  exit(3);
}