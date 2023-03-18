# Good Will Hunting (homeomorphically irreducible trees for a given n)

This program creates all possible homeomorphically irreducible trees for a user-specified n (a.k.a. all unique trees where all n nodes are connected and there aren't nodes with 2 edges) and outputs a graphviz file with all possible arrangements. Below is an example, for n = 10.

![graphviz](https://user-images.githubusercontent.com/90468276/225737079-675dd22e-3811-4fa4-b173-23fef8861e0e.png "Homeomorphically irreducible trees for n=10")

This is the second MIT-blackboard problem from the movie "Good Will Hunting", hence the name. The trees are constructed by finding every possible amount of edges (or seed) for every non-leaf node (a process I call decomposition), and arranging them in every possible unique combination (such combinations are obtained by running the same process on lower n values).

More details on how this program builds a solution can be found [here](https://santiagoalvz.wordpress.com/tag/good-will-hunting/).

## Arguments
The program expects at least one argument, n, which stands for the number of nodes.

`goodwillhunting N`

Other possible arguments are:
- **-o FILENAME, --output FILENAME:** Specifies a custom name for the output file. If not specified, 'output' will be used.
- **-v, --verbose:** This argument will print the whole arrangement table on screen. The arrangement table is divided by n-value, and for every arrangement it shows all the edges involved (in format [origin, destination]) and the arrangement's seed.
- **-h, --help:** displays help text

Short options (single character ones) can be grouped.

## Output
The output file is in .dot format and is expected to be fed into graphviz for the generation of an image. So far, neato has given the best-looking results, so it's recommended.
