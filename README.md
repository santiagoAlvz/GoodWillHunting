# Good Will Hunting (homeomorphically irreducible trees for a given n)

This program creates all possible homeomorphically irreducible trees for a user-specified n (a.k.a. all unique trees where all n nodes are connected and there aren't nodes with 2 connections) and outputs a graphviz file with all possible arrangements.

This is the second blackboard problem from the movie "Good Will Hunting", hence the name. The trees are constructed by finding every possible amount of edges (or seed) for every non-leaf node (a process I call decomposition), and arranging them in every possible unique combination (such combinations are obtained by running the same process on lower n values).

## Arguments
The program expects at least one argument, n, which stands for the number of nodes.

`goodwillhunting N`

Other possible arguments are:
- **-o FILENAME:** Specifies a custom name for the output file. If not specified, 'output' will be used.
- **-v:** from "verbose". This argument will print the whole arrangement table on screen. The arrangement table is divided by n-value, and for every arrangement it shows all the edges involved (in format [origin, destination]) and the arrangement's seed.

## Output
The output file is in .dot format and is expected to be fed into graphviz for the generation of an image. So far, neato has given the best-looking results, so it's recommended.
