# Password Entropy

You can estimate the strength of a password with the following formula, where `N` is the number of possible characters from which you're drawing your password, and `L` is the length of the password.

$$E = log_2(N^L)$$

Security is all about trade-offs between the value of whatever you are protecting, and the effort required to defeat the security measures. There are [tools available](https://www.openwall.com/john/) that will allow you to automate cracking a password, whether that's by brute-force, a dictionary-based attack, or a combination of the two.

It's generally desirable to have an entropy value greater than 100. At that point, it will either take an incredibly powerful supercomputer to break the password, or else it will take an inordinate amount of time.

## Examples

### WEAK EXAMPLE

`kwrzuubl`

Assuming all lowercase letters, `N` would be 26, and for an 8-character password, `L` would be 8.

$$log_2(N^L)  \Rightarrow  log_2(26^8) \Rightarrow log_2(208,827,064,576) \Rightarrow 37.603518$$

### STRONG EXAMPLE

`8hYOXgERzBCCC8MkqBip`

Assuming all uppercase and lowercase letters, as well as digits 0-9, `N` would be 62, and for a 20-character password, `L` would be 20...

$$log_2(N^L)  \Rightarrow  log_2(62^{20}) \Rightarrow log_2(704,423,425,546,997,948,163,318,836,497,481,728)
\Rightarrow 119.083926$$

### INSANELY STRONG

`6u?Gs6q9z,3ehqX7g1Og4P8mJ@pd.dmW`

Assume all uppercase and lowercase Roman letters, as well as digits 0-9, and the symbols `!`, `#`, `%`, `+`, `:`, `=`, `?`, `@`, `,`, and `.`, then `N` = 72, and `L` = 32...

$$log_2(N^L)  \Rightarrow  log_2(72^{32}) \Rightarrow log_2(2.7204445974 \cdot 10^{59}) \Rightarrow 197.437600$$
