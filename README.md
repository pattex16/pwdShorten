# pwdShort

![Alt text](./screenshot.png?raw=true)

My directory shortener for bash and zsh prompts inspired by [jonathonball's](https://github.com/jonathonball/pwd-shorten), that aims to be much faster on CPU cycles, because it is a compiled binary and nonetheless configurable!

## Requirements
- gcc, or any compiler really

## Compilation
- gcc main.c -o pwdShort

## Usage
pwdShort takes paths as standard arguments, first the current directory, then you home directory
- add pwdShort to your path
test it with
- echo $(pwdShort $PWD $HOME)

## Bash
- add $(pwdShort $PWD $HOME) to your PS1

## Zsh (this is my prompt!)
- PROMPT=' %B%F{green}%n%f%b@%B%F{blue}$(hostname | cut -c -5)%f%b:%F{yellow}%B$(pwdShort $PWD $HOME)%b%f%# '

## Example Output
The directory path in your prompt will be shortened:

    /very-long-directory-name/other-long-one/current_dir

becomes

    /ver+/oth+/current_dir

Home directories will be changed out as well:

    /home/selz/example/directory

becomes

    ~/exa+/directory

Dotfiles directories can be treated differently:

    /home/selz/.config/zsh

becomes

    ~/.con+/zsh

## Configuration
Despite my attempt to make this simple executable fast, it is still configurable through #define directives in main.c, you can change those to tweak the prompt as you like!

### Config Values

#### `SHORTENED_DIR_CHARS`
How much of the original subdirectory name to keep
- default: `3`

#### `HOME_SYMBOL`
The home symbol which will replace the home path
- default `~`

#### `REPLACEMENT_SYMBOL`
Symbol used to indicate that a directory name has been shortened.
- default `+`

#### `SEPARATOR_SYMBOL`
If you want to get fancy with custom separator symbols :P
- default `/`

#### `Dotdirs with one more char`
If you want to display one more character of directories that start with a dot
- by default i keep this on

### Example Configuration

    [settings]
    #define SHORTENED_DIR_CHARS 3
    #define HOME_SYMBOL '~'
    #define REPLACEMENT_SYMBOL '+'
    #define SEPARATOR_SYMBOL '/'

enjoy this! 
