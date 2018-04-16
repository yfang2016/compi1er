/*
 * ============================================================================
 *
 *       Filename:  format.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2018 06:01:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Fang Yuan (yfang@nju.edu.cn)
 *   Organization:  nju
 *
 * ============================================================================
 */


/* 
 * ===  FUNCTION  ============================================================
 *         Name:  format
 *  Description:  
 *      remove multiple whitespace, convert string to lowercase,
 * ===========================================================================
 */
int format (char *buf, char *line)
{
    char *src = line, *dst = buf, c;
    int sp;

    while(*src == ' ' || *src == '\t')	/* remove leading whitespace */
        src++;

    sp = 0;
	while(c = *src++) {
        if (c == ';' || c == '\n' || c == '\r')
        /* comment or return found */
            break;
        if (c == ' ' || c == '\t') {
            if (sp)  continue;
            else   sp = 1;  /* mark whitespace found */
        }
        if (c >= 'A' && c <= 'Z')
            c |= 0x20;
        *dst++ = c;
	}
    *dst = '\0';			/* end of line */
    return 0;
}		/* -----  end of function format  ----- */
