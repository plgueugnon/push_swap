chmod +x genstack.pl
 avant pour les droits d'exec :slight_smile:

usage: ./genstack stacksize min max

exemple 
./genstack 20 -1000 1000

pour une stack de 20 nombres compris entre -1000 et 1000

ARG=`./genstack.pl 20 0 1000`; ./push_swap $ARG | ./checker $ARG