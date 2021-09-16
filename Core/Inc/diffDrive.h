/*
 * diffDrive.h
 *
 *  Created on: 26 mai 2021
 *      Author: shado
 */



#ifndef INC_DIFFDRIVE_H_
#define INC_DIFFDRIVE_H_

#ifndef POS_STRUCT
#define POS_STRUCT
typedef struct {
	float theta, x, y ;
	float v, w;
} consign;
typedef struct {
	float x, y, theta;
} coor;
typedef struct {
	float w, v, vl, vr;
} velocity;
#endif

/**
 * Classe permettant de calculer les vitesses différentielles, c'est à dire les vitesse de la roue droite et celle de la roue gauche en
 * fonction de la vitesse de rotation linéaire et de la vitesse de rotation
 */
class diffDrive {
public:
	/**
	 * Constructeur de la classe ne prend pas de paramètres
	 */
	diffDrive();
	/**
	 * Obtient les valeur des vitesse différentielles gauche et droite en fonction des vitesses linéaire et de rotation.
	 * @param speed de type velocity*, paramètre contenant les vitesses linéaires et de rotation, les vitesses différentielles calculées sont enregistrés
	 */
	void getDiffSpeed(velocity* speed);
	/**
	 * Récupérer la valeur de la distance entre les deux roues motrices
	 * @return motDis retourne la distance -> retourne un float
	 */
	float getMotDis(){ return motDis; };
	/**
	 * Modifier la valeur de la distance entre les deux roues motrices
	 * @param motDis float: Nouvelle distance entre les deux roues motrices
	 */
	void setMotDis(float motDis){ this->motDis = motDis;};
private:
	float vr_Limit;
	float vl_Limit;
	float motDis;
};

#endif /* INC_DIFFDRIVE_H_ */
