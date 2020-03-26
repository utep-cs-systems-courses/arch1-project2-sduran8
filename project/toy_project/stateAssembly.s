	.arch msp430g2553

	.text
	.global toggle_green_a
toggle_green_a:
	cmp	#0, &red_on
	jz	else
	mov.b	#0, &green_on
	jmp	end
else:
	mov.b	#1, &green_on
end:
	mov.b 	#1, r12
	ret
