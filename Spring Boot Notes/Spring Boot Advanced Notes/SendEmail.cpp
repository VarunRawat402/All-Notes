--------------------------------------------------------------------------------------------------------------------------------------------
SendEmail:
--------------------------------------------------------------------------------------------------------------------------------------------

Sending email in Spring Boot is pretty straightforward 
Use JavaMailSender to send the Message through EmailService
Use SimpleMailMessage to create the message
Use MimeMessage to add attachments, templates etc etc in message

--------------------------------------------------------------------------------------------------------------------------------------------

Steps to Implement:

1: Add Dependency
2: Create App Password of gmail account from which you want to Send Email
3: Configure Properties
4: Autowired JavaMailSender ( Its bean will be automatically created when u configure the config )
5: Use SimpleMailMessage Class to create the mail
6: Use JavaMailSender to send the mail

--------------------------------------------------------------------------------------------------------------------------------------------

Dependency:
    <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-mail</artifactId>
    </dependency>

--------------------------------------------------------------------------------------------------------------------------------------------

Propeties:
    spring.mail.host=smtp.gmail.com
    spring.mail.port=587
    spring.mail.username=varunrawatstreetboys@gmail.com
    spring.mail.password=rblm vipp dfqv okkc
    spring.mail.properties.mail.smtp.auth=true
    spring.mail.properties.mail.smtp.starttls.enable=true

--------------------------------------------------------------------------------------------------------------------------------------------    

Simple Message:

Code:
@Service
public class EmailService {
    
    @Autowired
    private JavaMailSender javaMailSender;

    public void sendEmail(String to, String subject){

        SimpleMailMessage message = new SimpleMailMessage();

        String body = "Ye to majedaar mail hai bhaisab tahelka aamlet";
        message.setTo(to);
        message.setSubject(subject);
        message.setText(body);
        message.setFrom("varunrawatstreetboys@gmail.com");

        javaMailSender.send(message);
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Modified Message:

@Service
public class EmailService {

    @Autowired
    private JavaMailSender mailSender;

    public void sendHtmlMail(String to, String subject, String htmlBody) throws MessagingException {

        MimeMessage mimeMessage = mailSender.createMimeMessage();

        MimeMessageHelper helper = new MimeMessageHelper(mimeMessage, true); // `true` for multipart
        helper.setFrom("your_email@gmail.com");
        helper.setTo(to);
        helper.setSubject(subject);
        helper.setText(htmlBody, true); // true indicates HTML

        mailSender.send(mimeMessage);
    }
}

--------------------------------------------------------------------------------------------------------------------------------------------

Some Functionalities:

1. From Name:
helper.setFrom("Your Name <your_email@gmail.com>");

2. CC and BCC:
helper.setCc("cc@example.com");
helper.setBcc("bcc@example.com");

3: Attachments from Byte Array or InputStream
InputStreamSource source = new ByteArrayResource(fileBytes);
helper.addAttachment("filename.txt", source);

4:Multiple Attachments
helper.addAttachment("report1.pdf", new File("path/to/report1.pdf"));
helper.addAttachment("report2.pdf", new File("path/to/report2.pdf"));

--------------------------------------------------------------------------------------------------------------------------------------------