//Configuration des compteurs CTRA/CTRB pour la generation d'un signal.
void synth(long CTR_AB, long Pin, long Freq);

//Arret de la generation du signal pour le compteur CTRA
void silence_a(long Pin);

//Arret de la generation du signal pour le compteur CTRB
void silence_b(long Pin);

//Calcul de la frequence pour le registre FRQA/FRQB en fonction de l'horloge du syst�me
int fraction(long a, long b, long shift);

