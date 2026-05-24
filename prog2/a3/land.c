

//colisao do player com alguma coisa domundo buraco seila qualquer coisa
unsigned char collision_2D(struct body player, struct body cause_death){																																

	if ((((element_second->y-element_second->side/2 >= element_first->y-element_first->side/2) && (element_first->y+element_first->side/2 >= element_second->y-element_second->side/2)) || 	//				//Verifica se o primeiro elemento colidiu com o segundo no eixo X 
		((element_first->y-element_first->side/2 >= element_second->y-element_second->side/2) && (element_second->y+element_second->side/2 >= element_first->y-element_first->side/2))) && 	//				//Verifica se o segundo elemento colidiu com o primeiro no eixo X 
		(((element_second->x-element_second->side/2 >= element_first->x-element_first->side/2) && (element_first->x+element_first->side/2 >= element_second->x-element_second->side/2)) || 	//				//Verifica se o primeiro elemento colidiu com o segundo no eixo Y
		((element_first->x-element_first->side/2 >= element_second->x-element_second->side/2) && (element_second->x+element_second->side/2 >= element_first->x-element_first->side/2)))) return 1;			//Verifica se o segundo elemento colidiu com o primeiro no eixo Y
	else return 0;																																															
}