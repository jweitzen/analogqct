($path)= ($0 =~ /(.*\\)/); #The variable $0 contains the full path and name of this perl script. $path extracts the path only

$FilterFolder = shift (@ARGV);

$Filters_path = $FilterFolder."\\";
$TXT_temp_file_pathname=$path.'Temp.txt';
$HTML_temp_Left_file_pathname=$path.'LeftFrame.html';
$HTML_temp_Right_file_pathname=$path.'RightFrame.html';
$"="";

$CaseSensitive = shift (@ARGV);

foreach $Header (@ARGV)
{
	if ($Header)
	{
		$Filter_file_pathname = $Filters_path.$Header;
		open(INPUT,$Filter_file_pathname) || die "Can't open filter file" ;
		binmode INPUT;
#		@Strings_temp=<INPUT>;
#		close(INPUT);
#		foreach $String (@Strings_temp)
		while ( $String = <INPUT>)
		{
			$String =~ s/(STATE:(.*?)) COL\:/COL\:/;
			if ($2)
			{
				if ($2 eq "ON")
				{
					push(@Strings,$String);
				}
			}
		}
		close(INPUT);
	}
}

open (INPUT,$TXT_temp_file_pathname);
@lines_original=<INPUT>;
close(INPUT);

#Process the "Extended Debug Messages so they appear as in the Message View
$lines_processed="@lines_original";
$lines_processed =~ s/^.*?(\d\d:\d\d.*?)\s.*0x1FEB.*\n/$1   /mg;
#Explaining the Regular Expression above:
 #The first "s" indicates that is performing a substitution 
 #What appears between the first couples of / / is looked for and substituted with what appear in the second / /
 #The "m" at the end of the RegEx is the "multiline" modifier which means that the sunstitution will be restarted 
 #every time a line feed "\n" is met 
 #The "g" at the end means that the substitution must be repeated over and over until the end of the string
 #The "^" indicates "start of the line" so what follows must be right at the start of the line (which is, just
 #after a \n)
 #The ".*?" matches everything possible but is not "greedy" which means it will match as little as possible
 #The "(\d\d:\d\d.*?)\s" matches expressions like "14:32:53.456 " which is: two couples of digits followed by a 
 #colon then another couple of digits followed by any character up to the first space (the "\s" indicates space)
 #Notice that whatever is inclueded in the brackets "()" is then available in the variable "\1"
 #Then ".*0x1FEB\n" indicates: whatever character up to the string "0x1FEB" followed by whatever character and a 
 #carriage return ("\n")
 #Then the second part of the RegEx starts. The part where we decide what to substitue to the just found string
 #The "\1    " means: substitute what you find in the bracket () plus some spaces
$lines_processed =~ s/ \n.*Drop count.*\n\n//mg;

$lines_processed =~ s/^.*?(\d\d:\d\d.*?)\s.*0x1FFB(?:.*\n)*?.*Payload String =(.*)\n/$1   $2/mg;

open (OUTPUT,">$TXT_temp_file_pathname"); 
print OUTPUT $lines_processed;
close(OUTPUT);

open (INPUT,$TXT_temp_file_pathname);
@lines_original=<INPUT>;
close(INPUT);
@lines_processed=@lines_original;

$i = 0;
foreach $line (@lines_original)
{
			if ($line =~ /Channel Type = (.)(L_.*?),/)
			{
				$ChannelType = $1;
				if ($ChannelType eq "D")
				{$Fill = "|<-------|        |"}
				else {$Fill = "|------->|        |"}
				$Channel = $1.$2;
			}
			if ($line =~ s/(^.*?)  (message \w)/  $Fill $Channel  $2/)
			{$Fill = "";}
			
			if ($line =~ /Message Direction = (.*?) UE/)
			{
				$Direction = $1;
				if ($Direction eq "To")
				{$Fill = "|<----------------|"}
				else {$Fill = "|---------------->|"}
			}
			
			if ($line =~ /Direction = .* \((.*?)\)/)
			{
				$Direction = $1;
				if ($Direction eq "Downlink")
				{$Fill = "|<----------------|"}
				else {$Fill = "|---------------->|"}
			}
			
			if (($line =~ /prot/) && ($lines_original[$i+1] =~ /prot/) && ($lines_original[$i+2] =~ /    [A-Z]/))
			{
				$lines_original[$i+2] =~ s/(^.*?)(    [A-Z])/  $Fill NAS Message: $2/
			}
			
			$line =~ s/(^.*?)(value SysInfoType)/  $Fill BCCH  $2/;
			
			$lines_original[$i] = $line;
			$i++;
}

$Anchor=0;

foreach $String (@Strings)
{
	($String,$Colour,$Comment,$Replace,$With) = ($String =~ /STRING:(.*?) COL\:(.*?) COM\:(.*?) REPLACE\:(.*?) WITH\:(.*?)ENDOFLINE/);

	if ($String)
	{
#The two regex following allow the user to use regular expression special charcters lilke '[' '?' '*' etc.
#In AnaLog, in order to use a special character the user has to put a '!' in front of it. If a special character is left on
#its own, then Analog will 'escape' it so that perl will treat is a normal chracter. 'Escaping' in perl means putting a
#'\' in front of a chracter.
#So we now have to make a conversion. If the user want to match '?' with AnaLog he writes '?' but with Perl to match '?' 
#we have to write '\?'. On the other hand if the user wants to use '?' as a special character he has to write '!?' while
#for Perl we have to write '?'
#So, in order to achieve this conversion we do the following:
#1) we add a '\' in front of all special character we find in the string. In this way if the user wrote '?' we will now have 
#   '\?'. While, if the user wrote '!?' we will have '!\?'
#2) we remove all '!\' we find. As one can see this achieves what we need
		$String =~ s/([\[|\]|\\|\^|\$|\.|\||\?|\*|\+|\(|\)])/\\$1/g; #this add a '\' in front of all special character
		$String =~ s/!\\//g; #this removes all '!\' it can find
		if(!$Colour) {$Colour="000000";}
		if(!$Comment) {$Comment="";}
		else {$Comment="<FONT COLOR=FF0000> --> ".$Comment."</FONT>";}
		if (!$Replace) {$Replace="";}
		else
		{
			$Replace =~ s/([\[|\]|\\|\^|\$|\.|\||\?|\*|\+|\(|\)])/\\$1/g; #this add a '\' in front of all special character
			$Replace =~ s/!\\//g; #this removes all '!\' it can find		if(!$Colour) {$Colour="000000";}			
		}		
		if (!$With) {$With="";}
		else
		{
			$With =~ s/([\[|\]|\\|\^|\$|\.|\||\?|\*|\+|\(|\)])/\\$1/g; #this add a '\' in front of all special character
			$With =~ s/!\\//g; #this removes all '!\' it can find		if(!$Colour) {$Colour="000000";}			
		}	
		$i=0;
		@lines=@lines_original;
		foreach $line (@lines)
		{
			if ($line =~ /(\d\d:\d\d.*?)\s/)
			{
				$TimeStamp = $1;
			}	
		
			$Match = "";
			if ($CaseSensitive eq "CaseIsOFF")
			{
				$Match = ($line =~ /$String/i);
			}
			else
			{
				$Match = ($line =~ /$String/);
			}			
			if ($Match)
			{
				chop $line;
				if ($Replace) {$line =~ s/$Replace/$With/e;}
#	 			$line =~ s/<(.*?)$String(.*?)>/($1$String$2)/i;
	 			$line =~ s/<(.*?)>/($1)/i;
	 			if ($lines_processed[$i] =~ /^<.*>/)
				{
					$lines_processed[$i] = "<a name=\"$TimeStamp.$Anchor\">".$lines_processed[$i];
				}
				else
				{
					$lines_processed[$i]="<FONT COLOR=CC3300><a name=\"$TimeStamp.$Anchor\">$line</a></FONT>";
				}	
				$lines_processed[$i] = $lines_processed[$i].$Comment."\n";
				$line =~ s/\d\d:\d\d.*?\s//;
				$line = "<a href =\"RightFrame.html#$TimeStamp.$Anchor\" target=\"showframe\">$TimeStamp</a> <FONT COLOR=$Colour>".$line."</FONT>".$Comment."\n";

				if ($line =~ /\|.*?--.*?\|/)
				{
					$line = $line."               |        |        |\n";
				}
				push(@links,$line);
				$Anchor++;
			}
			$i++;
		}
	}	
}

@links = sort @links;

$"="\n";
$Strings="@Strings";
open (OUTPUT,">$HTML_temp_Left_file_pathname");
print OUTPUT "<html>\n<body>\n<pre>\n";
print OUTPUT "The program has extracted the following strings:\n$Strings\n\n";
print OUTPUT "\nTimestamp      UE       UTRAN    CN\n               |        |        |\n";
print OUTPUT @links;
print OUTPUT "</pre>\n</body>\n</html>\n";
close(OUTPUT);

open (OUTPUT,">$HTML_temp_Right_file_pathname");
print OUTPUT "<html>\n<body>\n<pre>\n";
print OUTPUT @lines_processed;
print OUTPUT "</pre>\n</body>\n</html>\n";
close(OUTPUT);

END:
1;
