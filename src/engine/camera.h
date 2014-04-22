#ifndef __CAMERA_H__
#define __CAMERA_H__

/****************************************************************/

/*
   Classe CAMERA:

   Encapsula as operacoes de transformacoes necessarias para
   fazer funcionar uma camera com livre movimentacao e giro em
   um mundo 3d.
   */
class CAMERA
{
    private:

        float posx, posy, posz;
        float angx, angy, angz;

    public:

        CAMERA();

        float GetPosX() {return posx;}
        float GetPosY() {return posy;}
        float GetPosZ() {return posz;}

        float GetAngX() {return angx;}
        float GetAngY() {return angy;}
        float GetAngZ() {return angz;}

        void GirarLado(float delta);

        void GirarFrente(float delta);

        void Posicionar();

        void BackwardsPosicionar();

        void Reposicionar();

        void Realinhar();

        void MoverFrente(float delta);

        void MoverLado(float delta);
};

/****************************************************************/

#endif /* #ifndef __CAMERA_H__ */
