#pragma once

#include <boost/program_options.hpp>

// TODO: why is there "do while()?"
#define debug_(A...) do { std::cout << A << std::endl; } while (0)

namespace po = boost::program_options;

/**
 * Struct that will hold the parsed argument values.
 */
struct ArgParseResult {
  // TODO: add arguments here
  // int num_verbose;
};

/**
 * Function that parses the arguments into a ArgParseResult object.
 *
 * @param argc The value of 'argc', as passed to main().
 * @param argv The value of 'argv', as passed to main().
 *
 * @return ArgParseResult object with the argument values.
 */
inline ArgParseResult arg_parser(int argc, char **argv) {
  debug_("Parsing arguments.");
  try {
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help", "print this help")
    ("version", "print program version")

    // ??
    ("formula,f", po::value<std::string>()->value_name("STRING"),
      "process the formula STRING")
    ("file,F", po::value<std::string>()->value_name("FILENAME[/COL]"),
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
    ("init,0", po::value<std::string>()->value_name("STATE"),
      "comma-separated state vector to use as initial state")
    ("ins,i", po::value<std::string>()->value_name("PROPS"),
      "comma-separated list of uncontrollable (a.k.a. input) atomic propositions")
    ("workers,j", po::value<std::string>()->value_name("VAL"),
      "Number of parallel workers for composition")
    ("outs,o", po::value<std::string>()->value_name("PROPS"),
      "comma-separated list of controllable (a.k.a. output) atomic propositions")
    ("synth,S", po::value<std::string>()->value_name("FILENAME"),
      "enable synthesis, pass .aag filename, or - to print gates")
    ("winreg,W", po::value<std::string>()->value_name("FILENAME"),
      "output winning region, pass .aag filename, or - to print gates")

    // fine tuning
    ("Kinc,I", po::value<std::string>()->value_name("VAL"),
      "increment value for K, used when Kmin < K")
    ("K", po::value<std::string>()->value_name("VAL"),
      "final value of K, or unique value if Kmin is not specified")
    ("Kmin,M", po::value<std::string>()->value_name("VAL"),
      "starting value of K; Kinc MUST be set when using "
                             "this option")
    ("unreal-x,u", po::value<std::string>()->value_name("[formula|automaton|both]"),
      "for unrealizability, either add X's to outputs in "
                             "the input formula, or push outputs one transition "
                             "forward in the automaton; with 'both', two "
                             "processes are started, one for each option "
                             "(default: both).")

    // output options
    ("check,c", po::value<std::string>()->value_name("[real|unreal|both]"),
      "either check for real, unreal, or both")
    // NOTE: this weird construction such that "verbose" can be specified multiple times
    ("verbose,v", po::value<std::vector<bool>>()
      ->default_value(std::vector<bool>(), "false")
      ->implicit_value(std::vector<bool>(1), "true")
      ->zero_tokens(),
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

    debug_("Finished parsing arguments.");

    return ArgParseResult();

  } catch (const std::exception& ex) {
    std::cout << ex.what() << std::endl;
    exit(3);
  }

  exit(3);
}