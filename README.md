<h1 align="center"> simpleRLE</h1>
<h3 align="center"> a simple run-length encoding system</h3>
<h3 align="left"> pros: </h3>

- compression ratio up to 85:1
- no unneeded data is stored
- can be used very well for compressing quantized DCT matrixes

<h3 align="left"> cons: </h3>

- not suitable for almost anything else
- does not use C strings
- size of uncompressed buffer not stored in compressed text

<h3 align="left"> how it works: </h3>
input data: hellooooo world
output data: hell5*o world

not exactly this way but somewhat like it. 
the compressed data can just be read from the file normally, except if the byte read is equal to 0x02 (2 in decimal)
```
struct block {
    unsigned char sign;
    unsigned char amount;
    unsigned char character;
};
```
the sign is always 0x02
the amount contains how long we need to repeat the character
and the 'character' key contains the value
so hello world would be stored as `hell\0x02\0x05o world`
0x02: indicates start of a block
0x05: length of repeated string
o = character to repeat

<br>