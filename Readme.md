# XFParse

Fast and simple file parser.

##Features
* Small and compact size.
* Easy and fast to use.
* Often updated.

## Installation

Simply include the xfparse header.

## Usage

Using xfparse is very easy.

The following txt file :
```
< Name : John >
< Age : 12 >
< Day : Monday >
< Precision : 0.01 >
```

Can be Read Like This :

```
XFParse parse;

parse.open("myfile.txt");

std::string mystring = parse.GetElement("Name");
```

numbers can be read like this :

```
int myint = parse.GetIntElement("Age");
```

## Contributing

1. Fork it!
2. Feel Free to push changes to this repository.