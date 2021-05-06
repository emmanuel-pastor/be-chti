	PRESERVE8
	THUMB   
		
	import LongueurSon
	import Son
	import PWM_Set_Value_TIM3_Ch3
	
	export CallbackSon
	export SortieSon

; ====================== zone de r�servation de donn�es,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
SortieSon dcw 0
Index dcd 0

	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
CallbackSon proc
	push {lr}
	;r1 = Index_pointer
	;r2 = Index
	ldr r1, =Index
	ldr r2, [r1]
	;r0 = Son[Index]
	ldr r0, =Son
	ldrsh r0, [r0, r2, LSL #1]
	;r3 = LongueurSon
	ldr r3, =LongueurSon
	ldr r3, [r3]
	
	;if (Index == LongueurSon) Fin
	cmp r2, r3
	beq Fin

	;else
	;convertir la valeur de Son de [-32768, 32767] � [0,719]
	;r0 = (Son+32768)*720/65535
	ldr r3, =32768
	add r0, r3
	ldr r3, =720
	mul r0, r3
	ldr r3, =65535
	udiv r0, r3
	
	;stocker la valeur convertie
	ldr r3, =SortieSon
	strh r0, [r3]
	
	;Index++
	add r2, #1
	str r2, [r1]

	;effectuer la PWM
	bl PWM_Set_Value_TIM3_Ch3
Fin
	pop {pc}
	endp
	
	END	