//Configuration des compteurs CTRA/CTRB pour la g�n�ration d'un signal.
void synth(long CTR_AB, long Pin, long Freq);

//Arr�t de la g�n�ration du signal pour le compteur CTRA
void silence_a(long Pin);

//Arr�t de la g�n�ration du signal pour le compteur CTRB
void silence_b(long Pin);

//Calcul de la fr�quence pour le registre FRQA/FRQB en fonction de l'horloge du syst�me
int fraction(long a, long b, long shift);

