# Operating-Systems

# Content
- Pratical classes' scripts (May contain errors, but this are the basis.)
- [Project](https://github.com/JoaoDiogoMota/sales-management-SO/tree/master/Operating-Systems-Project-master)

#### Projeto

In this project we intend to build a prototype of an inventory and sales management system. The system should consist of several programs: item maintenance, sales server, sales client, and data aggregator. 

##### Items management

This program should allow you to insert new items (specifying the name and sale price), or change attributes of a given item (name or price). Each article has a numeric code, assigned at creation as the next in a sequence (1, 2, 3, ...). In order for an article in the ARTICLES file to be accessed using the code as an index, the entries must have a fixed size. Since the name is of variable length, this attribute in the article file must contain only “references” (e.g., position) where they are found in a separate STRINGS file, containing their respective names.

```
$ ma
i <name> <price>         --> inserts new item, shows code
n <code> <new name>  --> change item's name
p <code> <new price>  --> change item's price
...
<EOF>
```

##### Sales server

This program should track stocks, receive customer sales orders, and record sales made. The stock quantity of each item must be kept in a single STOCKS file, for all items. Each sale must be registered by adding an entry to a SALES file, containing code, quantity and total amount of the sale.
The sales server must also arrange to run the aggregator on demand, causing it to receive the range (to be aggregated) of the sales file since the last aggregation, and having the result of the aggregation be written to a file whose name reflects the time the aggregation was requested (eg, 2019-03-29T14:23:56).

##### Sales customer 

The sales customer must interact with the sales server, requesting it to perform (a sequence of) operations that are easily distinguished by the number of parameters entered. One of the operations returns the quantity in stock and the price of an item (identified by the code). The other operation allows sales or entry into stock, specifying the code and quantity (negative or positive, respectively).

```
$ cv
<code>              --> returns to stdout stock and price
<code> <quantidade> --> updates stock and returns new stock
...
<EOF>
```

The system should allow concurrent execution of several sales customers. Test your work with two or more clients simultaneously "hammering" the same article!
User interaction with this sales customer is done only by stdin, with the results returned in stdout.

##### Aggregator

The aggregator program works as a filter. Receives entries in sales file format, up to end-of-file, via stdin. At that time, it produces to stdout the aggregated data of each item with sales made, containing the item code, the total quantity and the total sales amount of the respective item (keeping the sales file format).

## Collaborators

| Name            	|
|-----------------	|
| [Carolina Cunha](https://github.com/13caroline)  	|
| [Hugo Faria](https://github.com/KHiro13)      	|
| [João Diogo Mota](https://github.com/JoaoDiogoMota) 	|

> <img src="https://seeklogo.com/images/U/Universidade_do_Minho-logo-CB2F98451C-seeklogo.com.png" align="left" height="48" width="48" > University of Minho, Software Engineering (2nd Year).

