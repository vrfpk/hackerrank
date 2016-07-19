//#define NULL 0
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

typedef long Align;				// for alignment to long boundary

union header {					// block header
	struct {
		union header *ptr;		// next block if on free list
		unsigned size;			// size of this block
	} s;
	Align x;					// force alignment of blocks
};

typedef union header Header;

static Header base;				// empty list to get started
static Header *freep = NULL;	// start of free list

#define NALLOC 1024

// free: put block ap in free list
void mw_free(void *ap) {
	Header *bp, *p;

	bp = (Header *) ap - 1;				// point to block header
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;						// freed block at start or end of arena

	if (bp + bp->s.size == p->s.ptr) {	// join to upper nbr
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

// morecore: ask system for more memory
static Header *mw_morecore(unsigned nu) {
	char *cp, *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	//cp = sbrk(nu * sizeof(Header));
	cp = GlobalAlloc(GMEM_FIXED, nu * sizeof(Header));
	if (cp == (char *) -1)	// no space at all
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	mw_free((void *) (up + 1));
	return freep;
}

// malloc: general-purpose storage allocator
void *mw_malloc(unsigned nbytes) {
	Header *p, *prevp;
	unsigned nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {	// no free list yet
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {			// big enough
			if (p->s.size == nunits)		// exactly
				prevp->s.ptr = p->s.ptr;
			else {							// allocate tail end
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *) (p + 1);
		}
		if (p == freep)			// wrapped arround free list
			if ((p = mw_morecore(nunits)) == NULL)
				return NULL;	// none left
	}
	return NULL;
}

int main() {
	int g = 0;

	while ((g = _getch()) != 'q') {
		printf("g: %d, q: %d\n", g, 'q');
		mw_malloc(1000);
	}
	return 0;
}

