#pragma once
#include<iostream>
#include<string>
#include<Primitives/Shader.h>
#include<map>

using std::map;
using std::string;

//tipos

enum Type{
    NULO,
    NORMAL,
    FIGHTING,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    FIRE,
    WATER,
    GRASS,
    ELETRIC,
    PSYCHIC,
    ICE,
    DRAGON
};

//categoria de ataque
enum Category{
    PHYSICAL,
    SPECIAL,
    STATUS
};

//genero
enum Gender{
    MALE,
    FEMALE,
    NONID,
};


float effectiveChart[] = {
                        1.0f,    1.0f,   1.0f,    1.0f,  1.0f,  1.0f,   1.0f,     1.0f,  1.0f,    1.0f,   1.0f,   1.0f,   1.0f,    1.0f,      1.0f,    1.0f, //nulo
                        1.0f,    1.0f,   1.0f,    1.0f,  1.0f,  1.0f,   0.5f,     1.0f,  0.0f,    1.0f,   1.0f,   1.0f,   1.0f,    1.0f,      1.0f,    1.0f, //normal
                        1.0f,    2.0f,   1.0f,    0.5f,  0.5f,  1.0f,   2.0f,     0.5f,  0.0f,    1.0f,   1.0f,   1.0f,   1.0f,    0.5f,      2.0f,    1.0f, //fight 
                        1.0f,    1.0f,	 2.0f,	  1.0f,	 1.0f,	1.0f,   0.5f,	  2.0f,	 1.0f,	  1.0f,	  1.0f,	  2.0f,	  0.5f,	   1.0f,	  1.0f,	   1.0f, //Flying
                        1.0f,    1.0f,	 1.0f,	  1.0f,  0.5f,  0.5f,   0.5f,	  1.0f,  0.5f,	  1.0f,	  1.0f,	  2.0f,	  1.0f,	   1.0f,	  1.0f,	   1.0f, //Poison	
                        1.0f,    1.0f,	 1.0f,	  0.0f,	 2.0f,  1.0f,	2.0f,	  0.5f,	 1.0f,	  2.0f,	  1.0f,   0.5f,	  2.0f,	   1.0f,	  1.0f,    1.0f, //Ground	
                        1.0f,    1.0f,   0.5f,	  2.0f,	 1.0f,  0.5f,	1.0f,	  2.0f,	 1.0f,	  2.0f,	  1.0f,	  1.0f,	  1.0f,	   1.0f,	  2.0f,	   1.0f, //Rock	
                        1.0f,    1.0f,   0.5f,    0.5f,  0.5f,	1.0f,	1.0f,	  1.0f,  0.5f,	  0.5f,	  1.0f,	  2.0f,	  1.0f,	   2.0f,	  1.0f,	   1.0f, //Bug	
                        1.0f,    0.0f,	 1.0f,	  1.0f,	 1.0f,	1.0f,	1.0f,	  1.0f,	 2.0f,	  1.0f,	  1.0f,	  1.0f,	  1.0f,	   2.0f,	  1.0f,	   1.0f, //Ghost	
                        1.0f,    1.0f,	 1.0f,	  1.0f,	 1.0f,	1.0f,   0.5f,	  2.0f,	 1.0f,	  0.5f,	  0.5f,	  2.0f,	  1.0f,	   1.0f,	  2.0f,    0.5f, //Fire	
                        1.0f,    1.0f,	 1.0f,	  1.0f,	 1.0f,	2.0f,	2.0f,	  1.0f,	 1.0f,	  2.0f,	  0.5f,   0.5f,	  1.0f,	   1.0f,	  1.0f,    0.5f, //Water	
                        1.0f,    1.0f,	 1.0f,    0.5f,  0.5f,	2.0f,	2.0f,	  0.5f,	 1.0f,	  0.5f,	  2.0f,   0.5f,	  1.0f,	   1.0f,	  1.0f,    0.5f, //Grass	
                        1.0f,    1.0f,	 1.0f,	  2.0f,	 1.0f,	0.0f,	1.0f,	  1.0f,	 1.0f,	  1.0f,	  2.0f,   0.5f,	  0.5f,	   1.0f,	  1.0f,    0.5f, //Electric	
                        1.0f,    1.0f,	 2.0f,	  1.0f,	 2.0f,	1.0f,	1.0f,	  1.0f,	 1.0f,	  1.0f,	  1.0f,	  1.0f,	  1.0f,    0.5f,	  1.0f,	   1.0f, //Psychic	
                        1.0f,    1.0f,	 1.0f,	  2.0f,	 1.0f,	2.0f,	1.0f,	  1.0f,	 1.0f,	  0.5f,	  0.5f,	  2.0f,	  1.0f,	   1.0f,	  0.5f,	   2.0f, //Ice	
                        1.0f,    1.0f,	 1.0f,    1.0f,	 1.0f,	1.0f,	1.0f,	  1.0f,	 1.0f,	  1.0f,	  1.0f,	  1.0f,	  1.0f,	   1.0f,	  1.0f,	   2.0f  //Dragon	
};

float effectiveness(Type tipo1,Type tipo2){
    return effectiveChart[tipo2 + tipo1*16];
}



class Pokemon
{
    private:
        //moves 1
            int (*move1)(Pokemon, Pokemon) = nullptr;
            int mv1_usos_totais = 0;
            int mv1_atuais      = 0;
        //moves 2
            int (*move2)(Pokemon, Pokemon) = nullptr;
            int mv2_usos_totais = 0;
            int mv2_atuais      = 0;
        //moves 3
            int (*move3)(Pokemon, Pokemon) = nullptr;
            int mv3_usos_totais = 0;
            int mv3_atuais      = 0;
        //moves 4
            int (*move4)(Pokemon, Pokemon) = nullptr;
            int mv4_usos_totais = 0;
            int mv4_atuais      = 0;
        //status
        //non status
    public:
        Pokemon(){
        }
        void setMove(int moveNum, int(*func)(Pokemon, Pokemon), int maxPP){
            switch (moveNum)
            {
            case 1:
                this->move1 = func;
                this->mv1_usos_totais = maxPP;
                this->mv1_atuais = this->mv1_usos_totais;
                break;
            case 2:
                this->move2 = func;
                this->mv2_usos_totais = maxPP;
                this->mv2_atuais = this->mv2_usos_totais;
                break;
            case 3:
                this->move3 = func;
                this->mv3_usos_totais = maxPP;
                this->mv3_atuais = this->mv3_usos_totais;
                break;
            case 4:
                this->move4 = func;
                this->mv4_usos_totais = maxPP;
                this->mv4_atuais = this->mv4_usos_totais;
                break;
            default:
                break;
            }
        }

        int CallMove(int moveNum, Pokemon enemy){
            int retorno = 0;
             switch (moveNum)
            {
            case 1:
                if(this->move1 != nullptr){
                    retorno = this->move1(*this, enemy);
                }
                break;
            case 2:
                if(this->move2 != nullptr){
                    retorno = this->move2(*this, enemy);
                }
                break;
            case 3:
                if(this->move3 != nullptr){
                    retorno = this->move3(*this, enemy);
                }
                break;
            case 4:
                if(this->move4 != nullptr){
                    retorno = this->move4(*this, enemy);
                }
                break;
            default:
                break;
            }
            return retorno;
        }
};

struct Move
{
    int id;
    int (*func)(Pokemon, Pokemon);
    int pp;
    Move(int move_id, int(*funcao)(Pokemon, Pokemon), int pp_move){
        id   = move_id;
        func = funcao;
        pp   = pp_move;
    };
};




//funcoes que os moves chamam
//id = 1
int Pound(Pokemon pkm1, Pokemon pkm2){
    int power = 40;
    float acc = 1.0f;
    Type atkType = NORMAL;
    Category cat = PHYSICAL;
    std::cout << "Pound\n";
    return 1;
}
//id = 2
int Karate_Chop(Pokemon pkm1, Pokemon pkm2){
    int power = 50;
    float acc = 1.0f;
    Type atkType = FIGHTING;
    Category cat = PHYSICAL;
    std::cout << "Karate Chop\n";
    return 1;
}
//id = 3
int Double_Slap(Pokemon pkm1, Pokemon pkm2){
    int power = 15;
    float acc = 0.85f;
    Type atkType = NORMAL;
    Category cat = PHYSICAL;
    //pode acertar até 2 - 5 vezes;
    std::cout << "Double Slap\n";
    return 1;
}
//id = 4
int Comet_Punch(Pokemon pkm1, Pokemon pkm2){
    int power = 18;
    float acc = 0.85f;
    Type atkType = NORMAL;
    Category cat = PHYSICAL;
    //pode acertar até 2 - 5 vezes;
    std::cout << "Comet Punch\n";
    return 1;
}
//id = 5
int Mega_Punch(Pokemon pkm1, Pokemon pkm2){
    int power = 80;
    float acc = 0.85f;
    Type atkType = NORMAL;
    Category cat = PHYSICAL;
    std::cout << "Mega Punch\n";
    return 1;
}
//id = 6
int Pay_Day(Pokemon pkm1, Pokemon pkm2){
    int power = 40;
    float acc = 1.0f;
    Type atkType = NORMAL;
    Category cat = PHYSICAL;
    std::cout << "Pay Day\n";
    return 1;
}
//id = 7
int Fire_Punch(Pokemon pkm1, Pokemon pkm2){
    int power = 75;
    float acc = 1.0f;
    Type atkType = FIRE;
    Category cat = PHYSICAL;
    std::cout << "Fire Punch\n";
    return 1;
}
//onde os moves estao guardados
Move moves[] = {
    Move(1, Pound, 35),
    Move(2, Karate_Chop, 25),
    Move(3, Double_Slap, 10),
    Move(4, Comet_Punch, 15),
    Move(5, Mega_Punch,  20),
    Move(6, Pay_Day,  20),
    Move(7, Fire_Punch,  15),
};

/*
8	Ice Punch	Ice	Physical	15	75	100%	
9	Thunder Punch	Electric	Physical	15	75	100%	
10	Scratch	Normal	Physical	35	40	100%	
11	Vise Grip	Normal	Physical	30	55	100%	
12	Guillotine	Normal	Physical	5	—	30%	
13	Razor Wind	Normal	Special	10	80	100%	
14	Swords Dance	Normal	Status	20	—	—%	
15	Cut	Normal	Physical	30	50	95%	
16	Gust	Flying	Special	35	40	100%	
17	Wing Attack	Flying	Physical	35	60	100%	
18	Whirlwind	Normal	Status	20	—	—%	
19	Fly	Flying	Physical	15	90	95%	
20	Bind	Normal	Physical	20	15	85%	
21	Slam	Normal	Physical	20	80	75%	
22	Vine Whip	Grass	Physical	25	45	100%	
23	Stomp	Normal	Physical	20	65	100%	
24	Double Kick	Fighting	Physical	30	30	100%	
25	Mega Kick	Normal	Physical	5	120	75%	
26	Jump Kick	Fighting	Physical	10	100	95%	
27	Rolling Kick	Fighting	Physical	15	60	85%	
28	Sand Attack	Ground	Status	15	—	100%	
29	Headbutt	Normal	Physical	15	70	100%	
30	Horn Attack	Normal	Physical	25	65	100%	
31	Fury Attack	Normal	Physical	20	15	85%	
32	Horn Drill	Normal	Physical	5	—	30%	
33	Tackle	Normal	Physical	35	40	100%	
34	Body Slam	Normal	Physical	15	85	100%	
35	Wrap	Normal	Physical	20	15	90%	
36	Take Down	Normal	Physical	20	90	85%	
37	Thrash	Normal	Physical	10	120	100%	
38	Double-Edge	Normal	Physical	15	120	100%	
39	Tail Whip	Normal	Status	30	—	100%	
40	Poison Sting	Poison	Physical	35	15	100%	
41	Twineedle	Bug	Physical	20	25	100%	
42	Pin Missile	Bug	Physical	20	25	95%	
43	Leer	Normal	Status	30	—	100%	
44	Bite	Dark	Physical	25	60	100%	
45	Growl	Normal	Status	40	—	100%	
46	Roar	Normal	Status	20	—	—%	
47	Sing	Normal	Status	15	—	55%	
48	Supersonic	Normal	Status	20	—	55%	
49	Sonic Boom	Normal	Special	20	—	90%	
50	Disable	Normal	Status	20	—	100%	
51	Acid	Poison	Special	30	40	100%	
52	Ember	Fire	Special	25	40	100%	
53	Flamethrower	Fire	Special	15	90	100%	
54	Mist	Ice	Status	30	—	—%	
55	Water Gun	Water	Special	25	40	100%	
56	Hydro Pump	Water	Special	5	110	80%	
57	Surf	Water	Special	15	90	100%	
58	Ice Beam	Ice	Special	10	90	100%	
59	Blizzard	Ice	Special	5	110	70%	
60	Psybeam	Psychic	Special	20	65	100%	
61	Bubble Beam	Water	Special	20	65	100%	
62	Aurora Beam	Ice	Special	20	65	100%	
63	Hyper Beam	Normal	Special	5	150	90%	
64	Peck	Flying	Physical	35	35	100%	
65	Drill Peck	Flying	Physical	20	80	100%	
66	Submission	Fighting	Physical	20	80	80%	
67	Low Kick	Fighting	Physical	20	—	100%	
68	Counter	Fighting	Physical	20	—	100%	
69	Seismic Toss	Fighting	Physical	20	—	100%	
70	Strength	Normal	Physical	15	80	100%	
71	Absorb	Grass	Special	25	20	100%	
72	Mega Drain	Grass	Special	15	40	100%	
73	Leech Seed	Grass	Status	10	—	90%	
74	Growth	Normal	Status	20	—	—%	
75	Razor Leaf	Grass	Physical	25	55	95%	
76	Solar Beam	Grass	Special	10	120	100%	
77	Poison Powder	Poison	Status	35	—	75%	
78	Stun Spore	Grass	Status	30	—	75%	
79	Sleep Powder	Grass	Status	15	—	75%	
80	Petal Dance	Grass	Special	10	120	100%	
81	String Shot	Bug	Status	40	—	95%	
82	Dragon Rage	Dragon	Special	10	—	100%	
83	Fire Spin	Fire	Special	15	35	85%	
84	Thunder Shock	Electric	Special	30	40	100%	
85	Thunderbolt	Electric	Special	15	90	100%	
86	Thunder Wave	Electric	Status	20	—	90%	
87	Thunder	Electric	Special	10	110	70%	
88	Rock Throw	Rock	Physical	15	50	90%	
89	Earthquake	Ground	Physical	10	100	100%	
90	Fissure	Ground	Physical	5	—	30%	
91	Dig	Ground	Physical	10	80	100%	
92	Toxic	Poison	Status	10	—	90%	
93	Confusion	Psychic	Special	25	50	100%	
94	Psychic	Psychic	Special	10	90	100%	
95	Hypnosis	Psychic	Status	20	—	60%	
96	Meditate	Psychic	Status	40	—	—%	
97	Agility	Psychic	Status	30	—	—%	
98	Quick Attack	Normal	Physical	30	40	100%	
99	Rage	Normal	Physical	20	20	100%	
100	Teleport	Psychic	Status	20	—	—%	
101	Night Shade	Ghost	Special	15	—	100%	
102	Mimic	Normal	Status	10	—	—%	
103	Screech	Normal	Status	40	—	85%	
104	Double Team	Normal	Status	15	—	—%	
105	Recover	Normal	Status	5	—	—%	
106	Harden	Normal	Status	30	—	—%	
107	Minimize	Normal	Status	10	—	—%	
108	Smokescreen	Normal	Status	20	—	100%	
109	Confuse Ray	Ghost	Status	10	—	100%	
110	Withdraw	Water	Status	40	—	—%	
111	Defense Curl	Normal	Status	40	—	—%	
112	Barrier	Psychic	Status	20	—	—%	
113	Light Screen	Psychic	Status	30	—	—%	
114	Haze	Ice	Status	30	—	—%	
115	Reflect	Psychic	Status	20	—	—%	
116	Focus Energy	Normal	Status	30	—	—%	
117	Bide	Normal	Physical	10	—	—%	
118	Metronome	Normal	Status	10	—	—%	
119	Mirror Move	Flying	Status	20	—	—%	
120	Self-Destruct	Normal	Physical	5	200	100%	
121	Egg Bomb	Normal	Physical	10	100	75%	
122	Lick	Ghost	Physical	30	30	100%	
123	Smog	Poison	Special	20	30	70%	
124	Sludge	Poison	Special	20	65	100%	
125	Bone Club	Ground	Physical	20	65	85%	
126	Fire Blast	Fire	Special	5	110	85%	
127	Waterfall	Water	Physical	15	80	100%	
128	Clamp	Water	Physical	15	35	85%	
129	Swift	Normal	Special	20	60	—%	
130	Skull Bash	Normal	Physical	10	130	100%	
131	Spike Cannon	Normal	Physical	15	20	100%	
132	Constrict	Normal	Physical	35	10	100%	
133	Amnesia	Psychic	Status	20	—	—%	
134	Kinesis	Psychic	Status	15	—	80%	
135	Soft-Boiled	Normal	Status	5	—	—%	
136	High Jump Kick	Fighting	Physical	10	130	90%	
137	Glare	Normal	Status	30	—	100%	
138	Dream Eater	Psychic	Special	15	100	100%	
139	Poison Gas	Poison	Status	40	—	90%	
140	Barrage	Normal	Physical	20	15	85%	
141	Leech Life	Bug	Physical	10	80	100%	
142	Lovely Kiss	Normal	Status	10	—	75%	
143	Sky Attack	Flying	Physical	5	140	90%	
144	Transform	Normal	Status	10	—	—%	
145	Bubble	Water	Special	30	40	100%	
146	Dizzy Punch	Normal	Physical	10	70	100%	
147	Spore	Grass	Status	15	—	100%	
148	Flash	Normal	Status	20	—	100%	
149	Psywave	Psychic	Special	15	—	100%	
150	Splash	Normal	Status	40	—	—%	I
151	Acid Armor	Poison	Status	20	—	—%	I
152	Crabhammer	Water	Physical	10	100	90%	I
153	Explosion	Normal	Physical	5	250	100%	I
154	Fury Swipes	Normal	Physical	15	18	80%	I
155	Bonemerang	Ground	Physical	10	50	90%	I
156	Rest	Psychic	Status	5	—	—%	I
157	Rock Slide	Rock	Physical	10	75	90%	I
158	Hyper Fang	Normal	Physical	15	80	90%	I
159	Sharpen	Normal	Status	30	—	—%	I
160	Conversion	Normal	Status	30	—	—%	I
161	Tri Attack	Normal	Special	10	80	100%	I
162	Super Fang	Normal	Physical	10	—	90%	I
163	Slash	Normal	Physical	20	70	100%	I
164	Substitute	Normal	Status	10	—	—%	I
165	Struggle
*/

