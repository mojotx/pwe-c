# Password Entropy

You can estimate the strength of a password with the following formula, where `N` is the number of possible characters from which you're drawing your password, and `L` is the length of the password.

$$E = log_2(N^L)$$

Security is all about trade-offs between the value of whatever you are protecting, and the effort required to defeat the security measures. There are [tools available](https://www.openwall.com/john/) that will allow you to automate cracking a password, whether that's by brute-force, a dictionary-based attack, or a combination of the two.

It's generally desirable to have an entropy value greater than 100. At that point, it will either take an incredibly powerful supercomputer to break the password, or else it will take an inordinate amount of time.

## Why 100 bits?

An offline brute-force attack has to search, on average, half of a $2^E$ keyspace, where `E` is the entropy in bits. How long that takes depends entirely on how fast an attacker can try guesses, which in turn depends on how the password is stored:

| Hash / storage scheme                                                    | Realistic guess rate*            | Time to exhaust $2^{100}$ |
| ------------------------------------------------------------------------ | -------------------------------- | ------------------------- |
| Fast, unsalted hash (MD5, SHA-1, NTLM) on a large GPU/ASIC cracking farm | ~$10^{12}$–$10^{13}$ guesses/sec | Billions of years         |
| Properly salted, slow KDF (bcrypt, scrypt, Argon2)                       | ~$10^3$–$10^5$ guesses/sec       | Effectively infinite      |

\* These are pessimistic, attacker-favorable estimates, not real single-GPU numbers today; they intentionally leave headroom for future hardware (Moore's law/ASICs) and for quantum computers, since Grover's algorithm gives a quadratic speedup on unstructured search and effectively halves the *bit strength* of a brute-force search (i.e., a 100-bit password behaves more like ~50 bits against a large-scale quantum attacker).

Even under the pessimistic, fast-hash scenario, 100 bits leaves many orders of magnitude of safety margin, so it's still a reasonable, conservative target today. It also roughly tracks the ~128-bit security level that NIST recommends for cryptographic keys through 2030 and beyond — 100 bits is a bit below that "gold standard," but far beyond what's needed to resist any realistic brute-force attack, and it costs the user very little extra effort to type/store a slightly longer or richer password to get there.

## Important caveats

- **This formula only measures theoretical, best-case entropy.** It assumes every character is chosen independently and uniformly at random from the `N`-character alphabet. A human-chosen password of the same length and alphabet (e.g., `Password123!`) has dramatically *less* real-world entropy than this formula reports, because attackers use dictionaries, common substitutions (`a`→`@`), and pattern-aware rules rather than pure brute force. Use a password manager or a random generator if you want the calculated entropy to actually apply.
- **Raw entropy isn't the whole story.** [NIST SP 800-63B](https://pages.nist.gov/800-63-3/sp800-63b.html) and OWASP now emphasize length (12–15+ characters), screening against known-breached password lists, rate-limiting/lockout on login attempts, and slow, salted password hashing (bcrypt/scrypt/Argon2) on the server side — these controls often matter more in practice than hitting a specific entropy number, since they're what stand between an attacker and an offline brute-force attack in the first place.
- Given those caveats, "greater than 100 bits" remains reasonable advice for a *randomly generated* password/passphrase, but it's not a magic threshold — it's simply an extremely comfortable margin above what's brute-forceable today, chosen to absorb decades of hardware improvement.

## Examples

### WEAK EXAMPLE

Weak password: `kwrzuubl`

Assuming all lowercase letters, `N` would be 26, and for an 8-character password, `L` would be 8.

$$log_2(N^L)  \Rightarrow  log_2(26^8) \Rightarrow log_2(208,827,064,576) \Rightarrow 37.603518$$

### STRONG EXAMPLE

Strong password: `8hYOXgERzBCCC8MkqBip`

Assuming all uppercase and lowercase letters, as well as digits 0-9, `N` would be 62, and for a 20-character password, `L` would be 20...

$$log_2(N^L)  \Rightarrow  log_2(62^{20}) \Rightarrow log_2(704,423,425,546,997,948,163,318,836,497,481,728)
\Rightarrow 119.083926$$

### INSANELY STRONG

VERY strong password: `6u?Gs6q9z,3ehqX7g1Og4P8mJ@pd.dmW`

Assume all uppercase and lowercase Roman letters, as well as digits 0-9, and the symbols `!`, `#`, `%`, `+`, `:`, `=`, `?`, `@`, `,`, and `.`, then `N` = 72, and `L` = 32...

$$log_2(N^L)  \Rightarrow  log_2(72^{32}) \Rightarrow log_2(2.7204445974 \cdot 10^{59}) \Rightarrow 197.437600$$

## Password Entropy Calculator usage

The code is written in C, and uses the [GNU MPFR library](https://www.mpfr.org/) for working with very large numbers with accuracy and precision, as well as the [GNU Multiple Precision Arithmetic Library](https://gmplib.org/).

The code compiles cleanly on macOS and Linux, and should be straightforward to build on any UNIX-like operating system that's supported by MPFR.

### Mac compilation

On a Mac, you can just type "make" if you have the command-line developer tools installed. If you do NOT have the command-line development tools installed, you can install them with the `xcode-select --install` command. You will also need to install the GNU MPFR library, and IMHO the easiest way to do that is with the [Homebrew package manager](https://brew.sh), and `brew install mpfr`.

```text
$ make
clang -c -O -Wall -Wextra -fstack-protector-strong -pipe -MMD -arch x86_64 -mmacosx-version-min=13.0 pwe.c -o pwe.o
clang -O -Wall -Wextra -fstack-protector-strong -pipe -MMD -arch x86_64 -mmacosx-version-min=13.0 -o pwe pwe.o -lmpfr
```

### Linux compilation

On Linux, you will need a C compiler, GNU Make, and the GNU MPFR library installed, along with with GMP header files.

- **Debian, Ubuntu:** Run `apt install libmpfr-dev`
- **Red Hat, Rocky Linux, CentOS, Fedora:**  Run `dnf install mpfr-devel`
- **Alpine Linux:** Run `apk add mpfr-dev gmp-dev`.

```text
$ make
cc -c -O -Wall -Wextra -fstack-protector-strong -pipe -MMD pwe.c -o pwe.o
cc -O -Wall -Wextra -fstack-protector-strong -pipe -MMD -o pwe pwe.o -lmpfr
```
