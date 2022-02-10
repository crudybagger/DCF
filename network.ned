package pcf_dcf;

simple User
{
    gates:
        input in;
        output out;
}

simple AP
{
    gates:
        input in;
        output out;
}
network Network
{
    @display("bgb=755,376");
    submodules:
        ap: AP {
            @display("p=337,183");
        }
        user: User {
            @display("p=438,62");
        }
        user1: User {
            @display("p=477,144");
        }
        user2: User {
            @display("p=322,62");
        }
        user3: User {
            @display("p=222,318");
        }
        user4: User {
            @display("p=453,302");
        }
        user5: User {
            @display("p=209,112");
        }
    connections:
        
        user.out --> ap.in;
        ap.out --> user.in;
        
		user1.out --> ap.in;
		ap.out --> user1.in;
		
		user2.out --> ap.in;
		ap.out --> user2.in;
		
		user3.out --> ap.in;
		ap.out --> user3.in;
		
		user4.out --> ap.in;
		ap.out --> user4.in;
		
		user5.out --> ap.in;
		ap.out --> user5.in;
}
