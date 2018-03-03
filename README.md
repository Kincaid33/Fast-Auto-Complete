# Fast Auto Complete as a Ternary Search Tree

Autocomplete highly enhances user experience for two reasons: it minimises the number of keystrokes
needed to specify a string input, while at the same time helps users with a suggestion of useful closely
related inputs. Autocomplete typically wants to suggest the most likely strings that share the prefix
specified so far. Typically the prefix is extended every time a new keyboard event is triggered, hinting
that any successful autocomplete function should be as fast as the average human typist. Surveys
suggest that the average person types 200 characters per minute, which means that ideally our autocomplete
algorithm should not take longer than 0.3 seconds to suggest the correct autocompletion
candidates. If autocomplete takes much longer, users will dislike our solution. Another important
aspect is that more than one candidate should be suggested according to their likelihood. If we fail
suggesting the correct autocompletions users will not like our implementation either.

# Bugs Present
	1. Piping in a key_file return segmentation error
	2. Sorting is not efficient
	3. Sorting large file return segmentation error
	4. Stage 3 report incomplete requires more explanations
	5. Binary Search Tree implementation is not working: Test file included “test_yolinda.c”

Good Luck!

