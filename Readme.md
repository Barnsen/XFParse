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

These values in our example.txt file :
```
< Name : John >
< Age : 12 >
< Day : Monday >
< Precision : 0.01 >
```

Getting values:

```
XFParse parse;

parse.open("myfile.txt");

std::string mystring = parse.GetElement("Name");

int myint = parse.GetIntElement("Age");
```

Setting values:

```
parse.SetElement("Age", "13");
```

## Contributing

1. Fork it!
2. Feel Free to push changes to this repository.