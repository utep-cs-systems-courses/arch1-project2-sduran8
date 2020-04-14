	.arch msp430g2553

	;Assembly version of toggle_green
	.text
	.global toggle_green_a
toggle_green_a:
	cmp	#0, &red_on
	jz	else		;if red_on == 0
	mov.b	#0, &green_on
	jmp	end
else:
	mov.b	#1, &green_on
end:
	mov.b 	#1, r12
	ret


	
	;Assembly version of update_dim
	.data
new_red:
	.word 0
	
	.p2align 1,0
	.text
jt:
	.word off     ;[0]
	.word dim     ;[1]
	.word bright  ;[2]
	
	.global update_dim_a
update_dim_a:
	cmp	#3, &led_mode 	;led_mode - 3
	jhs 	fin		;if led_mode >= 3
	mov	&led_mode, r12
	add	r12, r12
	mov	jt(r12), r0
off:
	mov	#0, &new_red
	jmp	break
dim:
;	cmp 	#1, &count      ;(count < 1)
;	jhs 	off		;if count >= 1
;       jmp	bright
	call	#update_dim	;Using the CMP the runtime was to long so dim wouldnt work as intended
	jmp	fin
bright:
	mov	#1, &new_red
	jmp	break
break:
	cmp	&red_on, &new_red   ;(red_on != new_red)
	jeq	fin		    ;if red_on == new_red
	mov	&new_red, &red_on
	mov	#1, &led_changed
fin:
	ret
