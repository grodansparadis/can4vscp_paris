<TABLE cellspacing=4>
<tr><td class="menu_title" align='left'>Header One</td>
<tr><td><a href="doku.php?id=start" class="menu_item">introduction</a></td></tr>
<tr><td><a href="doku.php?id=more" class="menu_item">more</a></td></tr>
<tr><td><a href="doku.php?id=other:suff" class="menu_item">stuff</a> </td></tr>
<tr><td><a href="doku.php?id=other:features" class="menu_item">features</a> </td></tr>
<tr><td><a href="doku.php?id=other:items" class="menu_item">items</a> </td></tr>

<tr><td>&nbsp;</td> 
<tr><td class="menu_title" align='left'>Project</td>
<tr><td><a href="doku.php?id=project_notes" class="menu_item">project notes</a></td></tr>
<tr><td><a href="doku.php?id=change_log_1" class="menu_item">change log</a></td></tr>
<tr><td><a href="doku.php?id=change_log_2" class="menu_item">current changes</a> </td></tr>

<tr><td>&nbsp;</td> 
<tr><td class="menu_title" align='left'>Download</td>
<tr><td><a href="doku.php?id=download_page#download" class="menu_item">download</a> </td></tr>

<tr><td>&nbsp;</td> 
<tr><td class="menu_title" align='left'>Contact</td>
<tr><td>
  
 <?php
          $addr = _hide_email("you@example.com");
          $name = 'Contact'; 
          $email = "<a href=\"mailto:$addr\" class=\"menu_item\" style=\"font-weight:bold;\">$name</a>";   
          echo "&nbsp;$email";
 ?>
</td>
</TABLE>

