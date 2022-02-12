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
        input in1;
        output out1;
        input in2;
        output out2;
        input in3;
        output out3;
        input in4;
        output out4;
        input in5;
        output out5;
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
        
		user1.out --> ap.in1;
		ap.out1 --> user1.in;
		
		user2.out --> ap.in2;
		ap.out2 --> user2.in;
		
		user3.out --> ap.in3;
		ap.out3 --> user3.in;
		
		user4.out --> ap.in4;
		ap.out4 --> user4.in;
		
		user5.out --> ap.in5;
		ap.out5 --> user5.in;
}
