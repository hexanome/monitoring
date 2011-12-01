## Server to Client

    [type:char][size:int32][message:buffer(size)]

- 'i': info
- 'e': error

## Client to Server

    [type:char]

- type: 'i' init

    [type:char][numCommande:uint32][part_type:char][part_number:uint32][part_number_dif:int16]

- type: 'c' command
- numCommande: numéro de la commande
- part_type: 1, 2 (ou autre)
- part_number: nombre de pièce de type part_type
- part_number_dif: nombre de pièces différntes dans la commande

    [type:char][answer:char]

- type: 'a' answer
- answer : 'c' continue, 's' stop

---
